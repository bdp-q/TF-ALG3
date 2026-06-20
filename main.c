#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <geometria.h>

int *ant;
int *prox;
float *indiceOrig, *pontos;
int modo; // 1 quando -a ; 0 quando -h
float *erro;


float calcula_erro(int i)
{
    int a;
    int p;

    a  = ant[i];
    p = prox [i];

    if (modo == 1)
        return area_triangulo(indiceOrig[p], pontos[p], indiceOrig[i], pontos[i], indiceOrig[a], pontos[a]);
    else
        return altura2_triangulo(indiceOrig[p], pontos[p], indiceOrig[i], pontos[i], indiceOrig[a], pontos[a]);
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
        printf("-a\n");

    else if(strcmp(flag, "-h") == 0)
        printf("é -h\n"); //ao meu ver o jeito mais fácil é ativar uma variavel boolean ()
        // que vai dentro das funcoes chamadas na main pra indicar se usa a funcao do -a ou a do -h
    
    else{
        printf("Flag inválida: Use ou -a (tolerancia baseada na area do triangulo) ou -h (tolerancia baseada na altura)\n");
        return 1;
    }
    printf("%f\n",tolerancia);
    
    // programa em si
    int qnt_pares; 
    scanf("%d",&qnt_pares);

    // aloca os vetores (OBS: nao sei se vms usar mesmo os vetores alocados)
    // talvez de p contornar e eu so nao pensei como
    pontos = malloc(qnt_pares * sizeof(float));
    ant = malloc(qnt_pares * sizeof(int));
    prox = malloc(qnt_pares * sizeof(int));
    erro = malloc(qnt_pares * sizeof(float));
    indiceOrig = malloc(qnt_pares * sizeof(int));

    // mudei para ind 0
    for (int i=0; i < qnt_pares;i++)
        scanf("%f",&pontos[i]);

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

    for (int i=1;i<(qnt_pares - 1); i++)
        erro[i] = calcula_erro(i);
    //chama a função que remove os pontos que possuem tolerância

    //printa os pontos que restaram (num outro vetor?!)

    // tem que ser tudo log n
    
    // só pra ver se ta tudo certo
    // mudei para indice Origem, ja que se usar i vai ficar indexado em 0 agr
    for (int i=0; i < qnt_pares;i++)
        printf("%f %f\n",indiceOrig[i],pontos[i]);

    
    free(pontos);
    free(ant);
    free(prox);
    free(erro);
    free(indiceOrig);
    return 0; 
}