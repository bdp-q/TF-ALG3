#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

#define TAM_MAX 100

Heap *heap_cria(int capacity)
{
    Heap *heap;
    No **nos;

    // alocacao de memoria
    heap = malloc(sizeof(Heap));

    if (heap == NULL)
        return (NULL);

    nos = malloc(sizeof(No *) * capacity);

    if (nos == NULL)
    {
        free(heap);
        return (NULL);
    }

    // inicializacao
    heap->itens = nos;
    heap->tam = 0;
    heap->capacity = capacity;

    return (heap);
}

int heap_insere(Heap *heap, No *no)
{
    if (heap == NULL || no == NULL)
        return (-1);

    if (heap->tam >= heap->capacity)
        return (-1);

    No *aux;
    int aux_i;
    int i = heap->tam;

    // atribui no ao ultimo item do heap
    heap->itens[i] = no;
    heap->itens[i]->heap_index = i;

    // enquanto o erro do pai for maior, troca o filho com o pai e atualiza ponteiros
    while (i > 0 && heap->itens[(i - 1) / 2]->erro > heap->itens[i]->erro)
    {
        aux = heap->itens[(i - 1) / 2];
        heap->itens[(i - 1) / 2] = heap->itens[i];
        heap->itens[i] = aux;

        aux_i = heap->itens[(i - 1) / 2]->heap_index;
        heap->itens[(i - 1) / 2]->heap_index = heap->itens[i]->heap_index;
        heap->itens[i]->heap_index = aux_i;

        i = (i - 1) / 2;
    }

    heap->tam++;

    return (i);
}

No *heap_min(Heap *heap)
{
    if (heap == NULL || heap->tam == 0)
        return (NULL);

    return (heap->itens[0]);
}

int heap_sink(Heap *heap, No *no)
{
    if (heap == NULL || no == NULL)
        return (1);

    No *aux;
    No *son;
    int i = no->heap_index;
    int si;
    int aux_i;

    while (i < heap->tam)
    {
        if (2 * i + 1 >= heap->tam && 2 * i + 2 >= heap->tam)
            return (0);
        else if (2 * i + 2 >= heap->tam && 2 * i + 1 < heap->tam)
        {
            son = heap->itens[2 * i + 1];
            si = 2 * i + 1;
        }
        else if (heap->itens[2 * i + 1]->erro > heap->itens[2 * i + 2]->erro)
        {
            son = heap->itens[2 * i + 2];
            si = 2 * i + 2;
        }
        else
        {
            son = heap->itens[2 * i + 1];
            si = 2 * i + 1;
        }

        if (heap->itens[i]->erro <= son->erro)
            return (0);

        aux = heap->itens[si];
        heap->itens[si] = heap->itens[i];
        heap->itens[i] = aux;

        aux_i = heap->itens[si]->heap_index;
        heap->itens[si]->heap_index = heap->itens[i]->heap_index;
        heap->itens[i]->heap_index = aux_i;

        i = si;
    }
    return (0);
}

int heap_rise(Heap *heap, No *no)
{
    if (heap == NULL || no == NULL)
        return (1);

    No *aux;
    No *dad;
    int i = no->heap_index;
    int aux_i;

    while (i > 0)
    {
        dad = heap->itens[(i - 1) / 2];

        if (heap->itens[i]->erro > dad->erro)
            return (0);

        // se o erro do pai for menor do que o filho, troca os dois e atualiza ponteiros e index
        aux = heap->itens[i];
        heap->itens[i] = heap->itens[(i - 1) / 2];
        heap->itens[(i - 1) / 2] = aux;

        aux_i = heap->itens[i]->heap_index;
        heap->itens[i]->heap_index = heap->itens[(i - 1) / 2]->heap_index;
        heap->itens[(i - 1) / 2]->heap_index = aux_i;

        i = (i - 1) / 2;
    }
    return (0);
}

int heap_remove_min(Heap *heap)
{
    if (heap == NULL || heap->tam == 0)
        return (1);

    // se so tiver um elemento na lista, remove este elemento e a lista fica vazia
    if (heap->tam == 1)
    {
        free(heap->itens[0]);
        heap->itens[0] = NULL;

        heap->tam--;
        return (0);
    }

    No *aux = heap->itens[0];

    // troca a raiz com uma folha
    heap->itens[0] = heap->itens[heap->tam - 1];
    heap->itens[0]->heap_index = 0;
    heap->itens[heap->tam - 1] = aux;

    // liberacao de memoria
    free(heap->itens[heap->tam - 1]);
    heap->itens[heap->tam - 1] = NULL;

    heap->tam--;

    if (heap_sink(heap, heap->itens[0]) == 0)
        return (0);
    return (1);
}

int heap_update(Heap *heap, No *no, float novo_erro)
{
    if (heap == NULL || no == NULL || no->heap_index == -1)
        return (1);

    int is_lower = 0;
    int check;

    if (heap->itens[no->heap_index]->erro > novo_erro)
        is_lower = 1;

    heap->itens[no->heap_index]->erro = novo_erro;

    // verifica se o antigo erro do no eh maior que o novo:
    // - em caso positivo, o no sobe ate a posicao certa
    // - em caso negativo, o no desce ate a posicao certa
    if (is_lower == 1)
        check = heap_rise(heap, no);
    else
        check = heap_sink(heap, no);

    if (check == 0)
        return (0);
    return (1);
}

void heap_destroy(Heap **heap)
{
    if (heap == NULL || *heap == NULL)
        return;

    free((*heap)->itens);
    free(*heap);
    *heap = NULL;

    return;
}