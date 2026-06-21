#include <stdlib.h>
#include "no.h"

No *no_cria(int x, float y) {
    No *no;

    if(!(no = malloc(sizeof(No))))
        return NULL;

    no->ant = NULL;
    no->prox = NULL;
    no->x = x;
    no->y = y;

    no->erro = -1;

    no->heap_index = -1;

    return no;
}

void no_destroy(No **no) {
    if(no && *no) {
        free(*no);
        *no = NULL;
    }
}
