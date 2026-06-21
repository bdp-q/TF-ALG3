#include <stdlib.h>
#include "lista.h"

Lista *lista_create()
{
    Lista *lista;

    if (!(lista = malloc(sizeof(Lista))))
        return NULL;

    // inicializacao
    lista->ini = NULL;
    lista->fim = NULL;
    lista->tam = 0;

    return lista;
}

int lista_append(Lista *lista, No *no)
{
    if (!lista || !no)
        return -1;

    no->prox = NULL;
    no->ant = lista->fim;

    // se a fila estiver vazia, o no vira o primeiro, se nao, vira o ultimo
    if (lista->fim)
        lista->fim->prox = no;
    else
        lista->ini = no;

    lista->fim = no;
    (lista->tam)++;

    return 1;
}

int lista_remove(Lista *lista, No *no)
{
    if (!lista || !no)
        return -1;

    // se so tiver um no na lista, a lista fica vazia
    if (!(no->ant) && !(no->prox))
    {
        lista->ini = NULL;
        lista->fim = NULL;
        (lista->tam)--;

        return 1;
    }

    // se o no for o primeiro da lista, atualiza o lista->ini
    if (!(no->ant))
    {
        lista->ini = no->prox;
        no->prox->ant = NULL;
        (lista->tam)--;

        return 1;
    }

    // se o no for o ultimo da lista, atualiza o lista->fim
    if (!(no->prox))
    {
        lista->fim = no->ant;
        no->ant->prox = NULL;
        (lista->tam)--;

        return 1;
    }

    // se o no estiver no meio da lista, so atualiza ponteiros
    no->ant->prox = no->prox;
    no->prox->ant = no->ant;
    (lista->tam)--;

    return 1;
}

void lista_destroy(Lista **lista)
{
    No *no, *aux;

    if (lista && *lista)
    {
        no = (*lista)->ini;
        while (no != NULL)
        {
            aux = no->prox;
            no_destroy(&no);
            no = aux;
        }

        free(*lista);
        *lista = NULL;
    }
}