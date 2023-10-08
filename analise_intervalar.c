//Nome: Felipe Augusto Dittert Noleto; GRR:20205689
//Nome: Matheus Branco Barreto dos Santos; GRR:20203906

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fenv.h>
#include <string.h>
#include "analise_intervalar.h"

double proximo(double numero){
    return nextafter(numero, INFINITY);
}

double anterior(double numero){
    return nextafter(numero, -INFINITY);
}

void encontraIntervalo(intervalo *inter, char entrada[]){
    long double longo;
    if (strchr(entrada, 'e') != NULL){ //eh numero cientifico
        char final[5]; //expoente
        char positivo = 1;
        if (entrada[0] == '-') //eh negativo?
            positivo = 0;
        strcpy(final, (strchr(entrada, 'e')+1));//corta so o expoente
        int expoente = atoi(final);
        if (expoente < -4932){ //limite do long double
            if (positivo)
                longo = nextafterl(0, INFINITY);
            else
                longo = nextafterl(0, -INFINITY);
        }
        else{
            sscanf(entrada, "%Lf", &longo);
        }
    }
    else{
        sscanf(entrada, "%Lf", &longo);
    }
    
    double duplo = longo; //transforma long double em double, para encontrar o intervalo correto
    if (longo < duplo){ //numero de maquina eh maior que o proprio numero
        inter->maior = duplo;
        inter->menor = anterior(duplo);
        return;
    }
    else if(longo == duplo){ //numero de maquina eh o proprio numero
        inter->maior = duplo;
        inter->menor = duplo;
        return;
    }
    else{
        inter->maior = proximo(duplo); //menor que o proprio numero
        inter->menor = duplo;
        return;
    }
}

void imprime(intervalo inter){
    //primeiro numero
    if (!isinf(inter.menor)) //nao eh infinito
        printf("[%1.8e", inter.menor);
    else
        inter.menor > 0 ? printf("[+inf") : printf("[-inf"); //se for infinito
    
    //segundo numero
    if (!isinf(inter.maior))
        printf(", %1.8e]", inter.maior);
    else
        inter.maior > 0 ? printf(", +inf]") : printf(", -inf]");
}

void somar(intervalo *inter, intervalo *inter2){
    intervalo temp;
    fesetround(FE_UPWARD);
    temp.maior = inter->maior + inter2->maior;
    fesetround(FE_DOWNWARD);
    temp.menor = inter->menor + inter2->menor;
    *inter2 = temp;
}

void subtrair(intervalo *inter, intervalo *inter2){
    intervalo temp;
    fesetround(FE_DOWNWARD);
    temp.menor = inter->menor - inter2->maior;
    fesetround(FE_UPWARD);
    temp.maior = inter->maior - inter2->menor;
    *inter2 = temp;
}

void multiplicar(intervalo *inter, intervalo *inter2){
    intervalo temp;
    fesetround(FE_DOWNWARD);
    temp.menor = fminl(inter->menor, inter->maior) * fminl(inter2->menor, inter2->maior);
    fesetround(FE_UPWARD);
    temp.maior = fmaxl(inter->menor, inter->maior) * fmaxl(inter2->menor, inter2->maior);
    *inter2 = temp;
}

void dividir(intervalo *inter, intervalo *inter2){
    if (inter2->menor == 0 || inter2->maior == 0){ //divide por 0
        inter2->menor = -INFINITY;
        inter2->maior = INFINITY;
        return;
    }
    intervalo temp;
    temp.menor = inter->menor / inter2->maior;
    temp.maior = inter->maior / inter2->menor;
    *inter2 = temp;
}

void potencia(intervalo *inter, int p){
    if (p < 0)
        return;
    if (p == 0){
        inter->menor = 1;
        inter->maior = 1;
    }
    else if (p % 2 == 1 || (p % 2 == 0 && inter->menor >= 0)){ //p impar, ou p par com a >=0
        inter->menor = pow(inter->menor, p);
        inter->maior = pow(inter->maior, p);
    }
    else if(inter->maior < 0){ //p eh par, a e b < 0
        float temp = inter->menor;
        inter->menor = pow(inter->maior, p);
        inter->maior = pow(temp, p);
    }
    else{ //p eh par, a < 0 e b >= 0
        inter->menor = 0;
        inter->maior = fmaxl(pow(inter->menor, p), pow(inter->maior, p));
    }
}