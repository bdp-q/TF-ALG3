#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "geometria.h"
#include "heap.h"
#include "no.h"
#include "lista.h"

No **pontos;
int modo; // 1 quando modo = -a; 0 quando modo = -h

// define qual calculo sera realizado de acordo com o modo
float calcula_erro(No *ponto)
{
    No *a;
    No *p;

    a = ponto->ant;
    p = ponto->prox;

    if (modo == 1)
        return area_triangulo(a->x, a->y, ponto->x, ponto->y, p->x, p->y);
    else
        return altura2_triangulo(a->x, a->y, ponto->x, ponto->y, p->x, p->y);
}

int main(int argc, char *argv[])
{
    // tratamento dos parametros na linha de comando
    if (argc < 3)
    {
        printf("Uso: %s {-h ou -a}  {tolerancia em ponto flutuante}\n", argv[0]);
        return 1;
    }

    const char *flag = argv[1];
    const float tolerancia = (float)atof(argv[2]); // função que transforma o que foi escrito em parametro como float

    // define o modo de cálculo e, se inválido, avisa o usuário
    if (strcmp(flag, "-a") == 0)
        modo = 1;
    else if (strcmp(flag, "-h") == 0)
        modo = 0;
    else
    {
        printf("Flag inválida: Use ou -a (tolerancia baseada na area do triangulo) ou -h (tolerancia baseada na altura)\n");
        return 1;
    }

    // inicialização de variáveis do programa em si
    int qnt_pares;
    Heap *heap;
    Lista *lista;

    scanf("%d", &qnt_pares);
    heap = heap_cria(qnt_pares);
    lista = lista_create();

    if (!heap || !lista)
    {
        printf("Não foi possível iniciar o programa por falta de memória. Tente novamente.\n");
        return 1;
    }

    // alocação de vetor de pontos
    pontos = malloc(qnt_pares * sizeof(No *));

    // cria os nos os lendo e conectando na lista encadeada
    for (int i = 0; i < qnt_pares; i++)
    {
        float y;
        scanf("%f", &y);
        pontos[i] = no_cria(i + 1, y);
        if (lista_append(lista, pontos[i]) == -1)
        {
            printf("Não foi possível adicionar o elemento %d na lista. Tente novamente.\n", i + 1);
            lista_destroy(&lista);
            heap_destroy(&heap);
            free(pontos);
            return 1;
        }
    }

    // calcula os erros
    for (int i = 1; i < (qnt_pares - 1); i++)
    {
        No *no = pontos[i];
        no->erro = calcula_erro(no);
        no->heap_index = heap_insere(heap, no);
    }

    No *menor_erro = heap_min(heap);
    while (menor_erro && menor_erro->erro <= tolerancia)
    {
        No *ant = menor_erro->ant;
        No *prox = menor_erro->prox;

        pontos[menor_erro->x] = NULL;

        // tira o menor_erro da lista encadeada e do heap e trata erros
        if (lista_remove(lista, menor_erro) == -1)
        {
            printf("Não foi possível remover o item %d da lista. Tente novamente.\n", (int)menor_erro->x);
            lista_destroy(&lista);
            heap_destroy(&heap);
            free(pontos);
            return 1;
        }

        if (heap_remove_min(heap))
        {
            printf("Não foi possível remover o item %d do heap. Tente novamente.\n", (int)menor_erro->x);
            lista_destroy(&lista);
            heap_destroy(&heap);
            free(pontos);
            return 1;
        }

        // atualiza a posicao dos nos anterior e proximo no heap com os novos erros
        if (ant->heap_index != -1)
        {
            if (heap_update(heap, ant, calcula_erro(ant)))
            {
                printf("Não foi possível atualizar o item %d do heap. Tente novamente.\n", (int)ant->x);
                lista_destroy(&lista);
                heap_destroy(&heap);
                free(pontos);
                return 1;
            }
        }

        if (prox->heap_index != -1)
        {
            if (heap_update(heap, prox, calcula_erro(prox)))
            {
                printf("Não foi possível atualizar o item %d do heap. Tente novamente.\n", (int)prox->x);
                lista_destroy(&lista);
                heap_destroy(&heap);
                free(pontos);
                return 1;
            }
        }

        // menor_erro recebe nova raiz do heap
        menor_erro = heap_min(heap);
    }

    // imprime a lista final
    No *atual = lista->ini;
    printf("%d\n", lista->tam);
    while (atual != NULL)
    {
        printf("%d.0 %g\n", atual->x, atual->y);
        atual = atual->prox;
    }

    // libera memoria
    lista_destroy(&lista);
    heap_destroy(&heap);
    free(pontos);

    return 0;
}