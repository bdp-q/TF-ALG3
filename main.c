#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "geometria.h"
#include "heap.h"
#include "no.h"
#include "lista.h"

No **pontos;
int modo; // 1 quando -a ; 0 quando -h



float calcula_erro(No * ponto)
{
    No *a;
    No *p;
    
    a  = ponto->ant;
    p = ponto->prox;

    if (modo == 1)
        return area_triangulo(a->x, a->y, ponto->x, ponto->y,p->x, p->y);
    else
        return altura2_triangulo(a->x, a->y, ponto->x, ponto->y,p->x, p->y);
}
int main (int argc, char *argv[]){
    //tratamento dos parametros na linha de comando (peguei de prog 2)
    if(argc  < 3) {
        printf("Uso: %s {-h ou -a}  {tolerancia em ponto flutuante}\n", argv[0]);
        return 1;
    }

    const char *flag = argv[1];
    const float tolerancia = (float)atof(argv[2]); //função que transforma o que foi escrito em parametro como float

    if(strcmp(flag, "-a") == 0)
        modo = 1;

    else if(strcmp(flag, "-h") == 0)
        modo = 0; //ao meu ver o jeito mais fácil é ativar uma variavel boolean ()
        // que vai dentro das funcoes chamadas na main pra indicar se usa a funcao do -a ou a do -h
    
    else{
        printf("Flag inválida: Use ou -a (tolerancia baseada na area do triangulo) ou -h (tolerancia baseada na altura)\n");
        return 1;
    }
    
    // programa em si
    int qnt_pares; 
    scanf("%d",&qnt_pares);

    Heap *heap;
    heap = heap_cria(qnt_pares);

    Lista *lista;
    lista = lista_create();
    // aloca os vetores (OBS: nao sei se vms usar mesmo os vetores alocados)
    // talvez de p contornar e eu so nao pensei como
    pontos = malloc(qnt_pares * sizeof(No *));

    //cria os nos
    for (int i=0; i < qnt_pares;i++){
        float y;
        scanf("%f",&y);
        pontos[i] = no_cria(i+1,y);
        lista_append(lista, pontos[i]);
    }

    //calcula os erros
    for (int i=1; i < (qnt_pares-1);i++){
        No *no = pontos[i];
        no->erro = calcula_erro(no);
        no->heap_index = heap_insere(heap,no);
    }

    No *menor_erro = heap_min(heap);
    while(menor_erro && menor_erro->erro <= tolerancia){
        No* ant = menor_erro->ant;
        No* prox = menor_erro->prox;
        
        pontos[menor_erro->x] = NULL;
            //tem que tratar os erros na teoria
        //tira o menor_erro da lista encadeada    
        lista_remove(lista,menor_erro);
        if(heap_remove_min(heap))
            return 1;
        //atualiza a posicao no heap com os novos erros
        if(ant->heap_index != -1 )
            heap_update(heap,ant,calcula_erro(ant));
        if(prox->heap_index != -1 )
            heap_update(heap,ant,calcula_erro(prox));
        menor_erro = heap_min(heap);
    }
    No *atual = lista->ini;
    printf("%d\n",lista->tam);
    while(atual != NULL){
        printf("%d.0 %g\n",atual->x,atual->y);
        atual = atual->prox;
    }
    /*

    // preenche indexado no UM no vetor, para podermos usar index 0 no resto
    for (int i = 0; i < qnt_pares; i++)
        indiceOrig[i] = i + 1.0;
    
    // vetor de anterior
    for (int i=0;i<qnt_pares;i++)
        ant[i] = i - 1;
    
    // vetor de proximo 
    for (int i=0;i<qnt_pares;i++)
        prox[i] = i + 1;
    
    erro[0] = 1e9;
    erro[qnt_pares - 1] = 1e9;

    for (int i=1;i<(qnt_pares - 1); i++){
        no_cria(i,pontos[i],calcula_erro(i));
    }
    //chama a função que remove os pontos que possuem tolerância
    */
    //printa os pontos que restaram (num outro vetor?!)

    // tem que ser tudo log n
    
    // só pra ver se ta tudo certo
    // mudei para indice Origem, ja que se usar i vai ficar indexado em 0 agr


    lista_destroy(&lista);
    heap_destroy(&heap);
    free(pontos);

    return 0; 
}