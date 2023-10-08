//Nome: Felipe Augusto Dittert Noleto; GRR:20205689
//Nome: Matheus Branco Barreto dos Santos; GRR:20203906

#include <stdio.h>
#include <stdlib.h>
#include "analise_intervalar.h"
#include "eliminacao_gauss.h"
#include "metodo_minquad.h"

// Programa principal contendo apenas a função main():
int main(){

    int grau; //grau N
    scanf("%d", &grau);

    int QntPontos; //quantidade K de pontos
    scanf("%d", &QntPontos);

    ponto pontos[QntPontos]; //vetor com os pontos
    intervalo coeficientes[grau+1]; //vetor com os coeficientes Ai
    
    //criar matriz de intervalos [grau+1][grau+1]
    /* aloca um vetor de ponteiros para linhas */
    intervalo **matriz = malloc((grau+1) * sizeof(intervalo*));

    /* aloca cada uma das linhas da matriz A */
    for(int i=0; i<(grau+1); i++){
        matriz[i] = malloc((grau+1) * sizeof(intervalo));
    }

    //criar vetor B[grau+1]
    intervalo vetorB[grau+1];

//tgeraSL timer

    //lembrar de otimizar
    //preencherMatriz(matriz, grau, pontos)
    //for de for percorrendo a matriz
        //for pro somatorio com a formula
    
    //preencherVetor(vetor, grau, pontos)
    //for passando pelo vetor b
        //for pros somatorios

//tgeraSL timer

//tsolSL timer

    //triangulariza
    eliminacaoGauss(matriz, vetorB, grau+1);

    //resolve o sistema e encontra os coeficientes
    retrossubs(matriz, vetorB, coeficientes, grau+1);

//tsolSL timer

    //for percorrendo vetor de pontos, calculando os residuos
    //tudo de forma intervalar
    imprime_residuo(matriz, vetorB, coeficientes, grau+1);

    //leitura dos pontos
    for(int i = 0; i < QntPontos; i++){
        char entradaX[10], entradaY[10];
        scanf("%s %s", entradaX, entradaY);
        encontraIntervalo(&pontos[i].x, entradaX);
        encontraIntervalo(&pontos[i].y, entradaY);
    }

    return 0;
}