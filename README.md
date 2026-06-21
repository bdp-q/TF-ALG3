# TF-ALG3

Trabalho final da matéria de Algoritmos e estruturas de dados 3, ministrada Pelo professor Fabiano Silva na UFPR em 2026.1

_Grupo:_

- Breno Demio Padilha
- Fernanda Louize Manhães Teles Domingues
- Paola Siqueira Ceconello
- Pietro Francisco Andrade Sotile
- Rafaela Padilha Leitoles

_Estruturas utilizadas:_

- Vetor pontos[]: mapeia diretamente o índice x de um ponto para o ponteiro de um nó, em O(1). É a "tabela de símbolos" sugerida na especificação.
- heap_index guardado no No: evita precisar buscar a posição de um nó dentro do heap, fazendo com que o custo de localizar um nó seja O(1). Sem isso, realizar essa operação custaria O(n) (busca linear).
- Lista duplamente encadeada (ant/prox): permite, dado um nó, achar seu vizinho anterior e seguinte em O(1), e remover um nó do meio da lista em O(1) (só rearranja ant->prox e prox->ant).
- Min-heap (heap.c): array binário clássico, com heap_index sincronizado em cada troca (heap_insere, heap_sink, heap_rise).

_Porque cada operação custa log n:_

O heap é uma àrvore binária completa, ou seja, possui altura log n. Tendo isso em vista, bas considerar que toda operação que precisa "subir" ou "descer" um elemento percorre, no máximo, um caminho da raiz até uma folha, ou seja, no máximo log n trocas:

- heap_insere: insere no final do array e "sobe" (while comparando com o pai) → O(log n)
- heap_remove_min: troca a raiz com a última folha, remove e "desce" (heap_sink) → O(log n)
- heap_update: já recebe um ponteiro para o nó diretamente (não precisa buscar, porque o nó já tem heap_index), atualiza o campo erro e chama heap_rise ou heap_sink, dependendo se o erro aumentou ou diminuiu → O(log n)
  Assim, encontrar o nó é O(1) (graças ao heap_index armazenado no próprio nó), e reposicioná-lo depois da mudança de valor é O(log n). Essa combinação garante que remover um ponto e atualizar seus dois vizinhos custe O(log n) no máximo, não O(n).

_Por que a execução total é O(n log n):_

A main do programa possui 2 partes principais:

- Construção do heap (laços "for"): n inserções, cada uma O(log n) → O(n log n) no total.
- Laço principal de remoção (laço "while"): no pior caso, o laço executa até n − 2 vezes (todos os pontos intermediários podem ser removidos). Em cada iteração:
  - heap_remove_min → O(log n)
  - até 2 chamadas a heap_update (vizinho anterior e seguinte) → O(log n) cada
  - lista_remove → O(1)
  - calcula_erro → O(1) (só usa os 3 pontos: ant, ponto, prox)
    Cada iteração custa O(log n), e o laço roda no máximo n-2 vezes → O(n log n) no total.
    Somando as duas partes: O(n log n) + O(n log n) = O(n log n).
