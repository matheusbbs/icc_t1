//Nome: Felipe Augusto Dittert Noleto; GRR:20205689
//Nome: Matheus Branco Barreto dos Santos; GRR:20203906

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <likwid.h>
#include "analise_intervalar.h"
#include "eliminacao_gauss.h"
#include "metodo_minquad.h"

// Programa principal contendo apenas a função main():
int main(){

    //estrutura pros timers
    struct timeval tsolSL1, tsolSL2, tgeraSL1, tgeraSL2, tresiSL1, tresiSL2,
                    tsolSL1otim, tsolSL2otim, tgeraSL1otim, tgeraSL2otim, tresiSL1otim, tresiSL2otim;

    LIKWID_MARKER_INIT;

    int i, grau, qntPontos;
    scanf("%d", &grau); // grau N
    scanf("%d", &qntPontos); //quantidade K de pontos

    int tamanho = grau+1; // tamanho do sistema linear

    ponto *pontos = malloc(qntPontos * sizeof(ponto)); //vetor com os pontos
    intervalo *residuos = malloc(qntPontos * sizeof(intervalo)); // vetor com os residuosm
    intervalo coeficientes[tamanho]; // vetor com os coeficientes Ai
    intervalo vetorB[tamanho]; // cria vetor B [grau+1]

    // cria matriz de intervalos [grau+1][grau+1]
    intervalo **matriz = malloc(tamanho * sizeof(intervalo*));
    // aloca cada uma das linhas da matriz A
    for(i=0; i<tamanho; i++){
        matriz[i] = malloc(tamanho * sizeof(intervalo));
    }

    //le os pontos
    lerPontos(pontos, qntPontos);

//printf("Não otimizado:\n\n");
    //INICIO CALCULOS NAO OTIMIZADOS ----------

    //mede tempo antes de gerar valores
    gettimeofday(&tgeraSL1, NULL);

    LIKWID_MARKER_START("GeracaoSistemaLinear");

    //Metodo dos minimos quadrados
    preencherMatrizOtimizado(matriz, pontos, qntPontos, tamanho);
    preencherVetor(vetorB, pontos, qntPontos, tamanho);

    LIKWID_MARKER_STOP("GeracaoSistemaLinear");

    //depois de gerar
    gettimeofday(&tgeraSL2, NULL);

    //antes de solucionar
    gettimeofday(&tsolSL1, NULL);

    LIKWID_MARKER_START ("SolucaoSistemaLinear");

//debug
//printf("Imprimindo vetorB:\n");
//imprime_vetor(vetorB, tamanho);

    //triangulariza matriz
    eliminacaoGauss(matriz, vetorB, tamanho);

//debug
//printf("\nImprimindo vetorB após gauss:\n");
//imprime_vetor(vetorB, tamanho);
//printf("\n");

    //resolve o sistema encontrando os coeficientes
    retrossubs(matriz, vetorB, coeficientes, tamanho);

    LIKWID_MARKER_STOP ("SolucaoSistemaLinear");

    //depois de solucionar
    gettimeofday(&tsolSL2, NULL);

    //antes de calcular residuo
    gettimeofday(&tresiSL1, NULL);

    LIKWID_MARKER_START ("CalculoResiduos");

//debug
/*
printf("\n\nANTES DE CALCULAR residuos:");

printf("\npontos:\n");
imprime_vetor(pontos, qntPontos);

printf("\ncoeficientes:\n");
imprime_vetor(coeficientes, tamanho);

printf("\nresiduos:\n");
imprime_vetor(residuos, qntPontos);

printf("\nqntPontos:\n");
printf("%d", qntPontos);

printf("\ntamanho:\n");
printf("%d", tamanho);

printf("\n\n");
*/

    //calcula residuos
    calculaResiduo(pontos, coeficientes, residuos, qntPontos, tamanho);
//printf("\n\nDEPOIS DE CALCULAR residuos:\n");
//imprime_vetor(residuos, qntPontos);
//printf("\n\n");

    LIKWID_MARKER_STOP ("CalculoResiduos");

    //depois de calcular residuo
    gettimeofday(&tresiSL2, NULL);

    //FIM CALCULOS NAO OTIMIZADOS ----------

    //DEBUG
//imprime_sistema(matriz, vetorB, tamanho);
//printf("\n\n");
    //imprime vetor com coeficientes
//imprime_vetor(coeficientes, tamanho);
//printf("\n");

//imprime residuos
//imprime_vetor(residuos, qntPontos);
//printf("\n");

//printf("\n\nOtimizado:\n\n");

    //INICIO CALCULOS OTIMIZADOS -----------

    // cria matriz contínua de intervalos [grau+1][grau+1]
    intervalo *matrizCont = (intervalo *)malloc (tamanho * tamanho * sizeof(intervalo));
    intervalo vetorB2[tamanho]; // cria vetor B [grau+1]
    intervalo coeficientes2[tamanho]; // vetor com os coeficientes Ai
    intervalo *residuos2 = malloc(sizeof(intervalo) * qntPontos); // vetor com os residuosm

    //mede tempo antes de gerar valores
    gettimeofday(&tgeraSL1otim, NULL);

    LIKWID_MARKER_START("GeracaoSistemaLinearOtim");

    //Metodo dos minimos quadrados
    preencherMatrizOtimizadoV2(matrizCont, pontos, qntPontos, tamanho);
    preencherVetorV2(vetorB2, pontos, qntPontos, tamanho);

    LIKWID_MARKER_STOP("GeracaoSistemaLinearOtim");

    //depois de gerar
    gettimeofday(&tgeraSL2otim, NULL);

    //antes de solucionar
    gettimeofday(&tsolSL1otim, NULL);

    LIKWID_MARKER_START ("SolucaoSistemaLinearOtim");

//debug
//printf("Imprimindo vetorB2:\n");
//imprime_vetor(vetorB2, tamanho);

    //triangulariza matriz
    eliminacaoGaussV2(matrizCont, vetorB2, tamanho);

//debug
//printf("\nImprimindo vetorB2 após gauss:\n");
//imprime_vetor(vetorB2, tamanho);
//printf("\n");

    //resolve o sistema encontrando os coeficientes
    retrossubsV2(matrizCont, vetorB2, coeficientes2, tamanho);

    //debug
//printf("\n\nimprimindo coeficientes2:\n");
//imprime_vetor(coeficientes2, tamanho);
//printf("\n\n");

    LIKWID_MARKER_STOP ("SolucaoSistemaLinearOtim");

    //depois de solucionar
    gettimeofday(&tsolSL2otim, NULL);

    //antes de calcular residuo
    gettimeofday(&tresiSL1otim, NULL);

    LIKWID_MARKER_START ("CalculoResiduosOtim");

//debug
/*
printf("\n\nANTES DE CALCULAR residuos2:");

printf("\npontos:\n");
imprime_vetor(pontos, qntPontos);

printf("\ncoeficientes2:\n");
imprime_vetor(coeficientes2, tamanho);

printf("\nresiduos2:\n");
imprime_vetor(residuos2, qntPontos);

printf("\nqntPontos:\n");
printf("%d", qntPontos);

printf("\ntamanho:\n");
printf("%d", tamanho);

printf("\n\n");
*/

    //calcula residuos
    calculaResiduo(pontos, coeficientes2, residuos2, qntPontos, tamanho); //debugging
    //calculaResiduoV2(pontos, coeficientes2, residuos2, qntPontos, tamanho);
/*
printf("\n\nDEPOIS DE CALCULAR residuos2:");
printf("\nresiduos2:\n");
imprime_vetor(residuos2, qntPontos);
printf("\n\n");
*/
    LIKWID_MARKER_STOP ("CalculoResiduosOtim");

    //depois de calcular residuo
    gettimeofday(&tresiSL2otim, NULL);

    //FIM CALCULOS OTIMIZADOS -----------

    //DEBUG
//imprime_sistemaV2(matrizCont, vetorB2, tamanho);
//printf("\n\n");

    //imprime vetor com coeficientes
    imprime_vetor(coeficientes2, tamanho);
    printf("\n");

    //imprime residuos
    imprime_vetor(residuos2, qntPontos);
    printf("\n");

    //calcula e imprime a difenreca de tempos nao otimizados
    double diferencaTSolSL = (tsolSL2.tv_sec+tsolSL2.tv_usec/1000.0)-(tsolSL1.tv_sec+tsolSL1.tv_usec/1000.0);
    printf("TSolSL = %1.8e\n", diferencaTSolSL);
    double diferencaTGeraSL = (tgeraSL2.tv_sec+tgeraSL2.tv_usec/1000.0)-(tgeraSL1.tv_sec+tgeraSL1.tv_usec/1000.0);
    printf("TGeraSL = %1.8e\n", diferencaTGeraSL);
    double diferencaTResiSL = (tresiSL2.tv_sec+tresiSL2.tv_usec/1000.0)-(tresiSL1.tv_sec+tresiSL1.tv_usec/1000.0);
    printf("TResiSL = %1.8e\n", diferencaTResiSL);

    //calcula e imprime a difenreca de tempos otimizados
    double diferencaTSolSLOtim = (tsolSL2otim.tv_sec+tsolSL2otim.tv_usec/1000.0)-(tsolSL1otim.tv_sec+tsolSL1otim.tv_usec/1000.0);
    printf("TSolSLOtim = %1.8e\n", diferencaTSolSLOtim);
    double diferencaTGeraSLOtim = (tgeraSL2otim.tv_sec+tgeraSL2otim.tv_usec/1000.0)-(tgeraSL1otim.tv_sec+tgeraSL1otim.tv_usec/1000.0);
    printf("TGeraSLOtim = %1.8e\n", diferencaTGeraSLOtim);
    double diferencaTResiSLOtim = (tresiSL2otim.tv_sec+tresiSL2otim.tv_usec/1000.0)-(tresiSL1otim.tv_sec+tresiSL1otim.tv_usec/1000.0);
    printf("TResiSLOtim = %1.8e\n", diferencaTResiSLOtim);

    LIKWID_MARKER_CLOSE;
    free(pontos);
    free(residuos);
    // desaloca cada uma das linhas da matriz A
    for(i=0; i<tamanho; i++){
        free(matriz[i]);
    }
    free(matriz);
    free(matrizCont);
    free(residuos2);

    return 0;
}