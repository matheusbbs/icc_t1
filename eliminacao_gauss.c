//Nome: Felipe Augusto Dittert Noleto; GRR:20205689
//Nome: Matheus Branco Barreto dos Santos; GRR:20203906

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <likwid.h>
#include "analise_intervalar.h"

void imprime_sistema(intervalo **matriz, intervalo *vetorB, int tamanho){
    for(int i=0; i<tamanho; i++){
        for(int j=0; j<tamanho; j++)
            imprime(matriz[i][j]);
        imprime(vetorB[i]);
        printf("\n");
    }
}

void imprime_vetor(intervalo *vetor, int tamanho){
    int i;
    for(i=0; i<tamanho-1; i++)
        imprime(vetor[i]);
    imprime(vetor[i]);
}

uint encontraMax(intervalo **matriz, uint i, uint tamanho){
    double maior = fabs(matriz[i][i].maior);
    uint linha_maior = i;

    for(int lin=i+1; lin<tamanho; lin++)
        if (fabs(matriz[lin][i].maior) > maior){
            maior = fabs(matriz[lin][i].maior);
            linha_maior = lin;
        }
    
    return linha_maior;
}

void trocaLinhas(intervalo **matriz, intervalo *vetorB, int i, int iPivo){
    //troca linhas da matriz
    intervalo *aux = matriz[i];
    matriz[i] = matriz[iPivo];
    matriz[iPivo] = aux;

    //troca as posicoes do vetor B
    intervalo auxb = vetorB[i];
    vetorB[i] = vetorB[iPivo];
    vetorB[iPivo] = auxb;
}

void retrossubs(intervalo **matriz, intervalo *vetorB, intervalo *vetorX, int tamanho){

    /* da última linha até a primeira vai fazendo a retrossubstituição */
    for (int i = tamanho-1; i >= 0; --i){
        vetorX[i] = vetorB[i];

        /* percorre a linha a partir do segundo coeficiente */
        /* subtraindo as multiplicações (coeficiente * variavel) */
        for (int j = i+1; j < tamanho; ++j){
            intervalo temp = multiplicar(&matriz[i][j], &vetorX[j]);
            vetorX[i] = subtrair(&vetorX[i], &temp);
        }

        /* divide pelo valor que ta multiplicando a variavel, descobrindo seu valor */
        vetorX[i] = dividir(&vetorX[i], &matriz[i][i]);
    }
}

void eliminacaoGauss(intervalo **matriz, intervalo *vetorB, int tamanho){

    /* para cada uma das colunas, vai zerar tudo que ta abaixo do pivô */
    for(int i=0; i < tamanho; ++i){

        /* faz o pivoteamento parcial */
        uint iPivo = encontraMax(matriz, i, tamanho);
        if (i != iPivo)
            trocaLinhas(matriz, vetorB, i, iPivo);
        
        /* para cada linha abaixo do pivô, vai zerar o coeficiente */
        for(int k=i+1; k < tamanho; ++k){

            /* calcula o multiplicador, e zera */
            intervalo multiplicador = dividir(&matriz[k][i], &matriz[i][i]);
            encontraIntervaloLongo(&matriz[k][i], 0.0); //zera

            /* para cada elemento restante da linha, atualiza os coeficientes */
            for(int j=i+1; j < tamanho; ++j){
                intervalo temp = multiplicar(&matriz[i][j], &multiplicador);
                matriz[k][j] = subtrair(&matriz[k][j], &temp);
            }

            /* atualiza o termo independente */
            intervalo temp = multiplicar(&vetorB[i], &multiplicador);
            vetorB[k] = subtrair(&vetorB[k], &temp);
        }
    }
}