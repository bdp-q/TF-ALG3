#include <stdlib.h>
#include "no.h"

No *no_cria(float x, float y, float erro) {
    No *no;

    if(!(no = malloc(sizeof(No))))
        return NULL;

    no->ant = NULL;
    no->prox = NULL;
    no->x = x;
    no->y = y;

    no->erro = erro;

    return no;
}

void no_destroy(No **no) {
    if(no && *no) {
        free(*no);
        *no = NULL;
    }
}