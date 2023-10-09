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

void encontraIntervaloLongo(intervalo *inter, long double longo){
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
        printf(",%1.8e]", inter.maior);
    else
        inter.maior > 0 ? printf(",+inf]") : printf(",-inf]");
    printf("  ");
}

intervalo somar(intervalo *inter, intervalo *inter2){
    intervalo temp;
    fesetround(FE_UPWARD);
    temp.maior = inter->maior + inter2->maior;
    fesetround(FE_DOWNWARD);
    temp.menor = inter->menor + inter2->menor;
    return temp;
}

intervalo subtrair(intervalo *inter, intervalo *inter2){
    intervalo temp;
    fesetround(FE_DOWNWARD);
    temp.menor = inter->menor - inter2->maior;
    fesetround(FE_UPWARD);
    temp.maior = inter->maior - inter2->menor;
    return temp;
}

intervalo multiplicar(intervalo *inter, intervalo *inter2){
    intervalo temp;
    fesetround(FE_DOWNWARD);
    //calcula todas as possiveis multiplicacoes, guardando o menor e maior resultado
    double vetorMenor[4] = {inter->menor * inter2->menor, inter->menor * inter2->maior, inter->maior * inter2->menor, inter->maior * inter2->maior};
    temp.menor = vetorMenor[0];
    for (int i = 1; i < 4; i++){
        if (vetorMenor[i] < temp.menor)
            temp.menor = vetorMenor[i];
    }
    fesetround(FE_UPWARD);
    double vetorMaior[4]  = {inter->menor * inter2->menor, inter->menor * inter2->maior, inter->maior * inter2->menor, inter->maior * inter2->maior};
    temp.maior = vetorMaior[0];
    for (int i = 1; i < 4; i++){
        if (vetorMaior[i] > temp.maior)
            temp.maior = vetorMaior[i];
    }
    return temp;
}

intervalo dividir(intervalo *inter, intervalo *inter2){
    intervalo temp, segundo;
    if (inter2->menor == 0 || inter2->maior == 0){ //divide por 0
        temp.menor = -INFINITY;
        temp.maior = INFINITY;
        return temp;
    }
    //multiplica pelo inverso
    segundo.menor = 1/inter2->maior;
    segundo.maior = 1/inter2->menor;
    temp = multiplicar(inter, &segundo);
    return temp;
}

intervalo potencia(intervalo *inter, int p){
    intervalo temp;
    if (p < 0){
        fprintf(stderr, "potencia p deve ser >= 0");
        temp.menor = -1;
        temp.maior = -1;
        return temp;
    }
    if (p == 0){
        temp.menor = 1;
        temp.maior = 1;
    }
    else if (p % 2 == 1 || (p % 2 == 0 && inter->menor >= 0)){ //p impar, ou p par com a >=0
        fesetround(FE_DOWNWARD);
        temp.menor = pow(inter->menor, p);
        fesetround(FE_UPWARD);
        temp.maior = pow(inter->maior, p);
    }
    else if(inter->maior < 0){ //p eh par, a e b < 0
        double menor = inter->menor;
        fesetround(FE_DOWNWARD);
        temp.menor = pow(inter->maior, p);
        fesetround(FE_UPWARD);
        temp.maior = pow(menor, p);
    }
    else{ //p eh par, a < 0 e b >= 0
        temp.menor = 0;
        fesetround(FE_UPWARD);
        temp.maior = fmax(pow(inter->menor, p), pow(inter->maior, p));
    }
    return temp;
}