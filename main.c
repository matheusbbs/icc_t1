#include <stdio.h>
#include <stdlib.h>
#include "analise_intervalar.h"
#include "eliminacao_gauss.h"
#include "metodo_minquad.h"

struct Ponto{ //guarda x e y de um ponto
        intervalo x, y;
    }typedef ponto;

// Programa principal contendo apenas a função main():
int main(){

    int grau; //grau N
    scanf("%d", &grau);

    int QntPontos; //quantidade K de pontos
    scanf("%d", &QntPontos);

    ponto pontos[QntPontos]; //vetor com os pontos
    int coeficientes[grau]; //vetor com os coeficientes Ai

    for(int i = 0; i < QntPontos; i++){
        char entradaX[10], entradaY[10];
        scanf("%s %s", entradaX, entradaY);
        encontraIntervalo(&pontos[i].x, entradaX);
        encontraIntervalo(&pontos[i].y, entradaY);
    }
    
    return 0;
}