//Nome: Felipe Augusto Dittert Noleto; GRR:20205689
//Nome: Matheus Branco Barreto dos Santos; GRR:20203906

#include <stdio.h>
#include <stdlib.h>
#include <likwid.h>
#include "analise_intervalar.h"
#include "metodo_minquad.h"

//#include "eliminacao_gauss.h" // debug, para imprimir o sistema

void lerPontos(ponto *pontos, int qntPontos){
    for(int i = 0; i < qntPontos; i++){
        char entradaX[10], entradaY[10];
        scanf("%s %s", entradaX, entradaY);
        encontraIntervalo(&pontos[i].x, entradaX);
        encontraIntervalo(&pontos[i].y, entradaY);
    }
}

void preencherMatriz(intervalo **matriz, int tam, ponto *pontos, int qntPontos){
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            intervalo soma;
            encontraIntervaloLongo(&soma, 0);

            //calcula somatorio com a formula
            for(int k = 0; k < qntPontos; k++){
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

void preencherMatrizOtimizado(intervalo **matriz, ponto *pontos, int qntPontos, int tam){
    int i, j;
    for(i = 0; i < tam; i++){
        if(i == 0)  // só a primeira linha
            j=0;     
        else
            j=tam-1; // só a última coluna

        for(; j < tam; j++){
            intervalo soma;
            encontraIntervaloLongo(&soma, 0);

            //calcula somatorio com a formula
            for(int k = 0; k < qntPontos; k++){
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
            while(c >= 0 && l < tam){
                matriz[l][c] = soma;
                l++;
                c--;
            }
        }
    }
}

void preencherMatrizOtimizado2(intervalo **matriz, ponto *pontos, int qntPontos, int tam){
    int i, j;
    for(i = 0; i < tam; i++){
        if(i == 0)  // só a primeira linha
            j=0;     
        else
            j=tam-1; // só a última coluna

        if(i>0){ // copia todos os elementos (menos o último) da linha anterior
            for(int c=0; c<=tam-2; c++)
                matriz[i][c] = matriz[i-1][c+1];
        }

        for(; j < tam; j++){
            intervalo soma;
            encontraIntervaloLongo(&soma, 0);

            //calcula somatorio com a formula
            for(int k = 0; k < qntPontos; k++){
                intervalo mult1, mult2, mult;

                mult1 = potencia(&pontos[k].x, j);
                mult2 = potencia(&pontos[k].x, i);

                mult = multiplicar(&mult1, &mult2);

                soma = somar(&soma, &mult); // incrementa soma
            }
            matriz[i][j] = soma;
        }

        //printf("após calcular linha %d:\n", i);
        //imprime_sistema(matriz, pontos, tam);
    }
}

void preencherVetor(intervalo *vetor, ponto *pontos, int qntPontos, int tam){
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

void calculaResiduo(ponto *pontos, intervalo *coeficientes, intervalo *residuos, int qntPontos, int grau){
    //for percorrendo vetor de pontos, calculando os residuos
    for(int i=0; i<qntPontos; i++){
        intervalo coeficiente, pot, mult, soma;

        // calcula o valor da funcao naquele ponto
        encontraIntervaloLongo(&soma, 0); //soma = 0
        for(int j=0; j<grau; j++){
            //soma += Aj * X^j
            coeficiente = coeficientes[j];
            pot = potencia(&pontos[i].x, j);
            mult = multiplicar(&coeficiente, &pot);
            soma = somar(&soma, &mult);  // incrementa soma
        }
        residuos[i] = subtrair(&pontos[i].y, &soma); //calcula a diferenca
    }
}