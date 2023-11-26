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

void imprime_sistemaV2(intervalo *restrict matriz, intervalo *restrict vetorB, int tamanho){
    for(int i=0; i<tamanho; i++){
        for(int j=0; j<tamanho; j++)
            imprime(matriz[i *tamanho+ j]);
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

uint encontraMaxV2(intervalo *restrict matriz, uint i, uint tamanho){
    double maior = fabs(matriz[i *tamanho+ i].maior);
    
    uint linha_maior = i;

    for(int lin=i+1; lin<tamanho; lin++)
        if (fabs(matriz[lin *tamanho+ i].maior) > maior){
            maior = fabs(matriz[lin *tamanho+ i].maior);
            linha_maior = lin;
        }
    
    return linha_maior;
}

// se botar __restrict aqui, na matriz e no vetor, não muda nada
void trocaLinhas(intervalo **matriz, intervalo *vetorB, int i, int iPivo){
    //troca linhas da matriz
    //printf("\ntrocando ponteiros linhas [%d] e [%d]\n", i, iPivo);

    intervalo *aux = matriz[i];
    matriz[i] = matriz[iPivo];
    matriz[iPivo] = aux;

    //troca as posicoes do vetor B
    intervalo auxb = vetorB[i];
    vetorB[i] = vetorB[iPivo];
    vetorB[iPivo] = auxb;
}

// se botar __restrict aqui, na matriz e no vetor, não muda nada
void trocaLinhasV2(intervalo *restrict matriz, intervalo *restrict vetorB, int i, int iPivo, int tam){
    // Troca os elementos das linhas da matriz contínua
    int indiceLinha1 = i * tam;
    int indiceLinha2 = iPivo * tam;

    for (int k = 0; k < tam; k++) {
        //printf("\ntrocando elementos [%d] e [%d]\n", indiceLinha1 + k, indiceLinha2 +k);

        intervalo temp = matriz[indiceLinha1 + k];
        matriz[indiceLinha1 + k] = matriz[indiceLinha2 + k];
        matriz[indiceLinha2 + k] = temp;
    }

    //troca as posicoes do vetor B
    intervalo auxb = vetorB[i];
    vetorB[i] = vetorB[iPivo];
    vetorB[iPivo] = auxb;
}

// se botar __restrict aqui, no vetorX, não muda nada
void retrossubs(intervalo **matriz, intervalo *vetorB, intervalo *vetorX, int tamanho){

    /* da última linha até a primeira vai fazendo a retrossubstituição */
    for (int i = tamanho-1; i >= 0; --i){
        vetorX[i] = vetorB[i];

        //printf("\nvetorB[i] = ");
        //imprime(vetorB[i]);

        /* percorre a linha a partir do segundo coeficiente */
        /* subtraindo as multiplicações (coeficiente * variavel) */
        for (int j = i+1; j < tamanho; ++j){
            intervalo temp = multiplicar(&matriz[i][j], &vetorX[j]);
            vetorX[i] = subtrair(&vetorX[i], &temp);
        }

        /* divide pelo valor que ta multiplicando a variavel, descobrindo seu valor */
        vetorX[i] = dividir(&vetorX[i], &matriz[i][i]);
    }
    //printf("\n");
}

// se botar __restrict aqui, no vetorX, não muda nada
void retrossubsV2(intervalo *restrict matriz, intervalo *restrict vetorB, intervalo *restrict vetorX, int tamanho){

    /* da última linha até a primeira vai fazendo a retrossubstituição */
    for (int i = tamanho-1; i >= 0; --i){
        vetorX[i] = vetorB[i];

        //printf("\nvetorB[i] = ");
        //imprime(vetorB[i]);

        /* percorre a linha a partir do segundo coeficiente */
        /* subtraindo as multiplicações (coeficiente * variavel) */
        for (int j = i+1; j < tamanho; ++j){
            intervalo temp = multiplicarV2(&matriz[i *tamanho+ j], &vetorX[j]);
            vetorX[i] = subtrair(&vetorX[i], &temp);
        }

        /* divide pelo valor que ta multiplicando a variavel, descobrindo seu valor */
        vetorX[i] = dividirV2(&vetorX[i], &matriz[i *tamanho+ i]);
    }
    //printf("\n");
}

void eliminacaoGauss(intervalo **matriz, intervalo *vetorB, int tamanho){
    //printf("\tDentro da funcao eliminacaoGauss:\nantes:\n");
    //imprime_vetor(vetorB, tamanho);

//printf("\n\nImprimindo a matriz MATRIZ (antes da troca):\n");
//for(int a=0; a<tamanho; a++)
    //for(int b=0; b<tamanho; b++)
        //imprime(matriz[a][b]);
//printf("\n\n");

    /* para cada uma das colunas, vai zerar tudo que ta abaixo do pivô */
    for(int i=0; i < tamanho; ++i){

        /* faz o pivoteamento parcial */
        uint iPivo = encontraMax(matriz, i, tamanho);
        if (i != iPivo){
            trocaLinhas(matriz, vetorB, i, iPivo);
            // ^ tinha comentado essa linha sem querer. No T1 ela realmente existe
        }
        /* para cada linha abaixo do pivô, vai zerar o coeficiente */
        for(int k=i+1; k < tamanho; ++k){
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

// se botar __restrict aqui, na matriz e no vetor, não muda nada
// mesmo se tirar o if, não muda nada
void eliminacaoGaussV2(intervalo *restrict matriz, intervalo *restrict vetorB, int tamanho){
    /* para cada uma das colunas, vai zerar tudo que ta abaixo do pivô */
    for(int i=0; i < tamanho; ++i){

        /* faz o pivoteamento parcial */
        uint iPivo = encontraMaxV2(matriz, i, tamanho);
        if (i != iPivo){
            //printf("Trocando linhas %d e %d\n", i, iPivo);
            trocaLinhasV2(matriz, vetorB, i, iPivo, tamanho);
        }
        /* para cada linha abaixo do pivô, vai zerar o coeficiente */
        for(int k=i+1; k < tamanho; ++k){
            /* calcula o multiplicador, e zera */
            intervalo multiplicador = dividirV2(&matriz[k *tamanho+ i], &matriz[i *tamanho+ i]);
            encontraIntervaloLongo(&matriz[k *tamanho+ i], 0.0); //zera

            /* para cada elemento restante da linha, atualiza os coeficientes */
            for(int j=i+1; j < tamanho; ++j){
                intervalo temp = multiplicarV2(&matriz[i *tamanho+ j], &multiplicador);
                matriz[k *tamanho+ j] = subtrair(&matriz[k *tamanho+ j], &temp);
            }

            /* atualiza o termo independente */
            intervalo temp = multiplicarV2(&vetorB[i], &multiplicador);
            vetorB[k] = subtrair(&vetorB[k], &temp);
        }
    }
}