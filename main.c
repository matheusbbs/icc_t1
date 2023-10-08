//Nome: Felipe Augusto Dittert Noleto; GRR:20205689
//Nome: Matheus Branco Barreto dos Santos; GRR:20203906

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <likwid-marker.h>
#include "analise_intervalar.h"
#include "eliminacao_gauss.h"
#include "metodo_minquad.h"

// Programa principal contendo apenas a função main():
int main(){

    //estrutura pros timers
    struct timeval tsolSL1, tsolSL2, tgeraSL1, tgeraSL2;

    LIKWID_MARKER_INIT;

    int i, grau, qntPontos;
    scanf("%d", &grau); // grau N
    scanf("%d", &qntPontos); //quantidade K de pontos

    int tamanho = grau+1; // tamanho do sistema linear

    ponto pontos[qntPontos]; //vetor com os pontos
    intervalo coeficientes[grau+1]; // vetor com os coeficientes Ai
    intervalo vetorB[tamanho]; // cria vetor B [grau+1]

    // cria matriz de intervalos [grau+1][grau+1]
    intervalo **matriz = malloc(tamanho * sizeof(intervalo*));
    // aloca cada uma das linhas da matriz A
    for(i=0; i<tamanho; i++){
        matriz[i] = malloc(tamanho * sizeof(intervalo));
    }

    //le os pontos
    lerPontos(pontos, qntPontos);

    //mede tempo antes de gerar valores
    gettimeofday(&tgeraSL1, NULL);

    LIKWID_MARKER_START("geraSL");

    //Metodo dos minimos quadrados
    preencherMatrizOtimizado(matriz, pontos, qntPontos, tamanho);
    preencherVetor(vetorB, pontos, qntPontos, tamanho);
    
    LIKWID_MARKER_STOP("geraSL");

    //depois de gerar
    gettimeofday(&tgeraSL2, NULL);

    //antes de solucionar
    gettimeofday(&tsolSL1, NULL);

    LIKWID_MARKER_START ("solSL");

    //triangulariza matriz
    eliminacaoGauss(matriz, vetorB, grau+1);
    //resolve o sistema encontrando os coeficientes
    retrossubs(matriz, vetorB, coeficientes, grau+1);

    LIKWID_MARKER_STOP ("solSL");

    //depois de solucionar
    gettimeofday(&tsolSL2, NULL);

    //imprime vetor com coeficientes
    imprime_resultado(coeficientes, tamanho);
    printf("\n");

    //imprime residuos
    imprimeResiduoGauss(pontos, coeficientes, qntPontos, tamanho);
    printf("\n");

    //calcula e imprime a difenreca de tempos
    double diferencaTSolSL = (tsolSL2.tv_sec+tsolSL2.tv_usec/1000.0)-(tsolSL1.tv_sec+tsolSL1.tv_usec/1000.0);
    printf("%1.8e\n", diferencaTSolSL);
    double diferencaTGeraSL = (tgeraSL2.tv_sec+tgeraSL2.tv_usec/1000.0)-(tgeraSL1.tv_sec+tgeraSL1.tv_usec/1000.0);
    printf("%1.8e\n", diferencaTGeraSL);

    LIKWID_MARKER_CLOSE;

    return 0;
}