//Nome: Felipe Augusto Dittert Noleto; GRR:20205689
//Nome: Matheus Branco Barreto dos Santos; GRR:20203906

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "analise_intervalar.h"
#include "eliminacao_gauss.h"
#include "metodo_minquad.h"

// Atualizar essa função na eliminacao_gauss, e fica por lá
void imprime_sistema_inter(intervalo** A, intervalo* b, int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("[%lf,%lf] ", A[i][j].menor, A[i][j].maior);
        }
        printf("= [%lf,%lf]\n", b[i].menor, b[i].maior);
    }
    printf("\n");
}

void preencherMatriz(intervalo** matriz, int tam, ponto* pontos, int qntPontos){
    for(int i=0; i<tam; i++){
        for(int j=0; j<tam; j++){
            intervalo soma;
            encontraIntervaloLongo(&soma, 0);

            //calcula somatorio com a formula
            for(int k=0; k<qntPontos; k++){
                intervalo mult1, mult2, mult;

                mult1 = potencia(&pontos[k].x, j);
                mult2 = potencia(&pontos[k].x, i);

                mult = multiplicar(&mult1, &mult2);

                soma = somar(&soma, &mult); // incrementa soma
            }
            matriz[i][j] = soma;
        }
    }
}

// preenche a matriz de uma maneira otimizada, calculando só as diagonais
void preencherMatrizOtim(intervalo** matriz, int tam, ponto* pontos, int qntPontos){
    int i, j;
    for(i=0; i<tam; i++){
        if(i==0) j=0;     // só a primeira linha
        else     j=tam-1; // só a última coluna

        for(j; j<tam; j++){
            intervalo soma;
            encontraIntervaloLongo(&soma, 0);

            //calcula somatorio com a formula
            for(int k=0; k<qntPontos; k++){
                intervalo mult1, mult2, mult;

                mult1 = potencia(&pontos[k].x, j);
                mult2 = potencia(&pontos[k].x, i);

                mult = multiplicar(&mult1, &mult2);

                soma = somar(&soma, &mult); // incrementa soma
            }
            matriz[i][j] = soma;

            // Agora repete para as diagonais
            int l=i+1; // cópia da variável linha
            int c=j-1; // cópia da variável coluna
            while(c>=0 && l<tam){
                matriz[l][c] = soma;
                l++;
                c--;
            }
        }
    }
}

void preencherVetor(intervalo* vetor, int tam, ponto* pontos, int qntPontos){
    for(int i=0; i<tam; i++){
        intervalo soma;
        encontraIntervaloLongo(&soma, 0);

        //calcula somatorio (termos independentes)
        for(int k=0; k<qntPontos; k++){
            intervalo mult1, mult2, mult;

            mult1 = pontos[k].y;
            mult2 = potencia(&pontos[k].x, i);

            mult = multiplicar(&mult1, &mult2);

            soma = somar(&soma, &mult); // incrementa soma
        }
        vetor[i] = soma;
    }
}

// Programa principal contendo apenas a função main():
int main(){

    int i, j, k, grau, qntPontos;
    scanf("%d", &grau); // grau N
    scanf("%d", &qntPontos); //quantidade K de pontos

    ponto pontos[qntPontos]; //vetor com os pontos
    intervalo coeficientes[grau+1]; // vetor com os coeficientes Ai

    int tam = grau+1; // tamanho do sistema linear

    // cria matriz de intervalos [grau+1][grau+1]
    intervalo** matriz = malloc(tam * sizeof(intervalo));

    /* aloca cada uma das linhas da matriz A */
    for(i=0; i<tam; i++){
        matriz[i] = malloc(tam * sizeof(intervalo));
    }

    // cria vetor B [grau+1]
    intervalo vetor[tam];

    //leitura dos pontos
    for(int i = 0; i < qntPontos; i++){
        char entradaX[10], entradaY[10];
        scanf("%s %s", entradaX, entradaY);
        encontraIntervalo(&pontos[i].x, entradaX);
        encontraIntervalo(&pontos[i].y, entradaY);
    }

    // preenche a matriz
    preencherMatrizOtim(matriz, tam, pontos, qntPontos);

    // preencher o vetor
    preencherVetor(vetor, tam, pontos, qntPontos);
    
    // para visualizar apenas
    imprime_sistema_inter(matriz, vetor, tam);










































//tsolSL timer

    //triangulariza
    //eliminacaoGauss(matriz, vetor, grau+1)

    //resolve o sistema e encontra os coeficientes
    //retrossubs(matriz, vetor b, coeficientes, grau+1)

//tsolSL timer

    //calcularResiduos();
    //for percorrendo vetor de pontos, calculando os residuos
    //tudo de forma intervalar

    

    return 0;
}