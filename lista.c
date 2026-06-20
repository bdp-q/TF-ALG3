#include <stdlib.h>
#include "lista.h"

Lista *lista_create() {
    Lista *lista;

    if (!(lista = malloc(sizeof(Lista))))
        return NULL;

    lista->ini = NULL;
    lista->fim = NULL;
    lista->tam = 0;

    return lista;
}

int lista_append(Lista *lista, No *no) {
    if(!lista || !no)
        return -1;
    
    no->prox = NULL;
    no->ant = lista->fim;

    if(lista->fim)
        lista->fim->prox = no;
    else
        lista->ini = no;


    lista->fim = no;
    (lista->tam)++;

    return 1;
}

int lista_remove(Lista *lista, No *no) {
    if(!lista || !no)
        return -1;
    
    if(!(no->ant) && !(no->prox)) {
        lista->ini = NULL;
        lista->fim = NULL;
        (lista->tam)--;
        
        return 1;
    }

    if(!(no->ant)) {
        lista->ini = no->prox;
        no->prox->ant = NULL;
        (lista->tam)--;

        return 1;
    }
    if(!(no->prox)) {
        lista->fim = no->ant;
        no->ant->prox = NULL;
        (lista->tam)--;

        return 1;
    }

    no->ant->prox = no->prox;
    no->prox->ant = no->ant;
    (lista->tam)--;

    return 1;
}

void lista_destroy(Lista **lista) {
    No *no, *aux;

    if(lista && *lista) {
        no = (*lista)->ini;
        while(no != NULL) {
            aux = no->prox;
            no_destroy(&no);
            no = aux;
        }

        free(*lista);
        *lista = NULL;
    }
}