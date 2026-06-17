#ifndef LISTA_H
#define LISTA_H
#include "no.h"

typedef struct {
    No *ini;
    No *fim;
    int tam;
} Lista;

/*
 * Cria uma lista duplamente encadeada vazia
 *
 * Retorno: Lista * se sucesso, NULL se erro
 */
Lista *lista_create();

/*
 * Adiciona um elemento na última posição da lista
 *
 * Retorno: 1 se sucesso, -1 se erro
 */
int lista_append(Lista *lista, No *no);

/*
 * Remove o elemento passado pelo parâmetro
 * 
 * Retorno: 1 se sucesso, 0 se lista vazia e -1 se erro
*/
int lista_remove(Lista *lista, No *no);

/*
 * Desaloca a memória utilizada pela lista e faz *lista receber NULL
 */
void lista_destroy(Lista **lista);

#endif