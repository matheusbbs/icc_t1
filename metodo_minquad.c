//Nome: Felipe Augusto Dittert Noleto; GRR:20205689
//Nome: Matheus Branco Barreto dos Santos; GRR:20203906

#include <stdio.h>
#include <stdlib.h>
#include <likwid.h>
#include "analise_intervalar.h"
#include "metodo_minquad.h"

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

void imprimeResiduo(ponto *pontos, intervalo *coeficientes, int qntPontos, int grau){
    //for percorrendo vetor de pontos, calculando os residuos
    for(int i=0; i<qntPontos; i++){
        intervalo coeficiente, pot, mult, soma, valor_residuo;

        // calcula o valor da funcao naquele ponto
        encontraIntervaloLongo(&soma, 0); //soma = 0
        for(int j=0; j<grau; j++){
            //soma += Aj * X^j
            coeficiente = coeficientes[j];
            pot = potencia(&pontos[i].x, j);
            mult = multiplicar(&coeficiente, &pot);
            soma = somar(&soma, &mult);  // incrementa soma
        }
        valor_residuo = subtrair(&pontos[i].y, &soma); //calcula a diferenca
        imprime(valor_residuo);
    }
}