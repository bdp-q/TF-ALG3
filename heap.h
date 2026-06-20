#ifndef HEAP_H
#define HEAP_H
#include "no.h"

typedef struct {
    No **itens;
    int tam;
    int capacity;
} Heap;

/*
 * Cria um min heap vazio
 *
 * Retorno: Heap * se sucesso, NULL se erro
 */
Heap *heap_cria(int capacity);

/*
 * Adiciona um elemento em um heap seguindo a regra do min-heap
 *
 * Retorno: posição no Heap se sucesso, -1 se erro
 */
int heap_insere(Heap *heap, No *no);

/*
 * Retorna o elemento de menor prioridade sem remover
 * 
 * Retorno: Ponteiro para o nó, NULL se erro ou vazio
*/
No *heap_min(Heap *heap);

/*
 * Remove o primeiro elemento do heap e reorganiza o heap
 * 
 * Retorno: 0 se sucesso, 1 se erro
*/
int heap_remove_min(Heap *heap);

/*
 * Atualiza o campo erro do no e reorganiza o heap após a alteração
 * 
 * Retorno: 0 se sucesso, 1 se erros
*/
int heap_update(Heap *heap, No *no, float novo_erro);

/*
 * Desaloca a memória utilizada pelo heap e faz *heap receber NULL
 */
void heap_destroy(Heap **heap);

#endif