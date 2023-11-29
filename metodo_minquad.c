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
        char entradaX[100], entradaY[100];
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

// se botar __restrict aqui, na matriz, não muda nada
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

// se botar __restrict aqui, na matriz, não muda nada
void preencherMatrizOtimizadoV2Prototipo(intervalo **matriz, ponto *pontos, int qntPontos, int tam){
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

/* se botar __restrict aqui, na matriz, não muda nada
   acho que não tem como vetorizar isso de maneira nenhuma, tem muitos ifs dentro do laço,
   e esses ifs realmente são necessários para a otimização que foi usada */
void preencherMatrizOtimizadoV2(intervalo *restrict matriz, ponto *restrict pontos, int qntPontos, int tam){
    int i, j;
    for(i = 0; i < tam; i++){
        //if(i == 0)  // só a primeira linha
            //j=0;     
        //else
            //j=tam-1; // só a última coluna
        j = (i == 0) ? 0 : (tam - 1); // substitui os ifs acima por esse operador ternário
        // mesmo assim nao ta vetorizando

        if(i>0){ // copia todos os elementos (menos o último) da linha anterior
            for(int c=0; c<=tam-2; c++)
                matriz[i *tam+ c] = matriz[(i-1) *tam+ (c+1)];
        }

        for(; j < tam; j++){
            intervalo soma;
            encontraIntervaloLongo(&soma, 0);

            //calcula somatorio com a formula
            for(int k = 0; k < qntPontos; k++){
                intervalo mult1, mult2, mult;

                mult1 = potenciaV2(&pontos[k].x, j);
                mult2 = potenciaV2(&pontos[k].x, i);

                mult = multiplicarV2(&mult1, &mult2);

                soma = somar(&soma, &mult); // incrementa soma
            }
            matriz[i *tam+ j] = soma;
        }

        //printf("após calcular linha %d:\n", i);
        //imprime_sistema(matriz, pontos, tam);
    }
}

// se botar __restrict aqui, no vetor, não muda nada
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

// se botar __restrict aqui, no vetor, não muda nada
// as chamadas das funcoes de intervalos não deixam vetorizar pois tem muitos ifs dentro delas:
//   encontraIntervaloLongo, potenciaV2
void preencherVetorV2(intervalo *restrict vetor, ponto *restrict pontos, int qntPontos, int tam){
    for(int i=0; i<tam; i++){
        intervalo soma;
        encontraIntervaloLongo(&soma, 0);

        //calcula somatorio (termos independentes)
        for(int k=0; k<qntPontos; k++){
            intervalo mult1, mult2, mult;

            mult1 = pontos[k].y;
            mult2 = potenciaV2(&pontos[k].x, i);

            mult = multiplicarV2(&mult1, &mult2);

            soma = somar(&soma, &mult); // incrementa soma
        }
        vetor[i] = soma;
    }
}

// se botar __restrict aqui, no vetor residuos, não muda nada
void calculaResiduo(ponto *pontos, intervalo *coeficientes, intervalo *residuos, int qntPontos, int grau){
    //for percorrendo vetor de pontos, calculando os residuos
    for(int i=0; i<qntPontos; i++){
        intervalo coeficiente, pot, mult, soma;

        // calcula o valor da funcao naquele ponto
        encontraIntervaloLongo(&soma, 0); //soma = 0

//printf("\n\n\n\nDENTRO DA FUNÇÃO calculaResiduo: i=%d",i);
//printf("\nsoma = "); imprime(soma);
        for(int j=0; j<grau; j++){
//printf("\nj=%d",j);
            //soma += Aj * X^j
            coeficiente = coeficientes[j];
//printf("\n\tcoeficiente = "); imprime(coeficiente);
            pot = potencia(&pontos[i].x, j);
//printf("\n\tpot = "); imprime(pot);
            mult = multiplicar(&coeficiente, &pot);
//printf("\n\tmult = "); imprime(mult);
            soma = somar(&soma, &mult);  // incrementa soma
//printf("\n\tsoma = "); imprime(soma);
        }
        residuos[i] = subtrair(&pontos[i].y, &soma); //calcula a diferenca
//printf("\n\tresiduos[%d] = ",i); imprime(residuos[i]);
    }
}

// se botar __restrict aqui, no vetor residuos, não muda nada
// as chamadas das funcoes de intervalos não deixam vetorizar pois tem muitos ifs dentro delas:
//   encontraIntervaloLongo, potenciaV2
void calculaResiduoV2(ponto *restrict pontos, intervalo *restrict coeficientes, intervalo *restrict residuos, int qntPontos, int grau){
    //for percorrendo vetor de pontos, calculando os residuos
    for(int i=0; i<qntPontos; i++){
        intervalo coeficiente, pot, mult, soma;

        // calcula o valor da funcao naquele ponto
        encontraIntervaloLongo(&soma, 0); //soma = 0
        for(int j=0; j<grau; j++){
            //soma += Aj * X^j
            coeficiente = coeficientes[j];
            pot = potenciaV2(&pontos[i].x, j);
            mult = multiplicarV2(&coeficiente, &pot);
            soma = somar(&soma, &mult);  // incrementa soma
        }
        residuos[i] = subtrair(&pontos[i].y, &soma); //calcula a diferenca
    }
}