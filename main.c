#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    float pontos[qnt_pares+1]; //acho que isso talvez mude, coloquei + 1 pra nao ter ponto 0 mas n sei oq é melhor
    for (int i=1; i <= qnt_pares;i++)
        scanf("%f",&pontos[i]);
    
    //chama a função que remove os pontos que possuem tolerância

    //printa os pontos que restaram (num outro vetor?!)

    // tem que ser tudo log n
    
    // só pra ver se ta tudo certo
    for (int i=1; i <= qnt_pares;i++)
        printf("%d.0 %f\n",i,pontos[i]);


    return 0; 
}