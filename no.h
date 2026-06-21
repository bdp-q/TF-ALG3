#ifndef NO_H
#define NO_H

typedef struct No
{
    int x;
    float y;
    struct No *prox;
    struct No *ant;
    float erro; // área ou altura ao quadrado
    int heap_index;
} No;

/*
 * Cria No * e preenche os campos com parâmetros informados
 *
 * Retorno: No * se sucesso, NULL se erro
 */
No *no_cria(int x, float y);

/*
 * Desaloca a memória utilizada pelo ponteiro *no e faz *no receber NULL
 *
 */
void no_destroy(No **no);

#endif
