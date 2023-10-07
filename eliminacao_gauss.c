#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void imprime_sistema(double** A, double* b, int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            printf("%.0lf ", A[i][j]);
        printf("%.0lf\n", b[i]);
    }
    printf("\n");
}

void imprime_resultado(double *x, int tam){
    printf("X       = [ ");
    int i;
    for(i=0; i<tam-1; i++)
        printf("%.5lf       ", x[i]);
    printf("%.5lf       ]\n", x[i]);
}

void imprime_residuo(double **matriz, double *vetor, double *x, int tam){
    printf("Residuo = [ ");
    /* percorre as linhas */
    double residuo = 0;
    for(int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){ /* percorre as colunas */
            residuo += matriz[i][j]*x[j];
        }
        residuo -= vetor[i];
        printf("%1.5e   ", residuo);
        residuo = 0;
    }
    printf("]\n");
}

/* encontra o valor máximo (em módulo) de uma coluna i da matriz A de tamanho n */
// retorna a linha que contém o valor máximo
uint encontraMax(double** A, uint i, uint n){
    double maior = fabs(A[i][i]);
    uint linha_maior = i;

    for(int lin=i+1; lin<n; lin++)
        if (fabs(A[lin][i]) > maior){
            maior = fabs(A[lin][i]);
            linha_maior = lin;
        }
    
    return linha_maior;
}

/* Troca as linhas i, iPivo da matriz A e do vetor B */
void trocaLinhas(double** A, double* b, int i, int iPivo){

    void* aux = A[i];
    A[i] = A[iPivo];
    A[iPivo] = aux;

    double auxb = b[i];
    b[i] = b[iPivo];
    b[iPivo] = auxb;
}

/* Seja um Sistema Linear de ordem n */
/* Matriz de coeficientes A, Vetor de termos independentes B, valor das variáveis X */
void retrossubs(double** A, double* b, double* x, int n){

    /* da última linha até a primeira vai fazendo a retrossubstituição */
    for (int i = n-1; i >= 0; --i){
        x[i] = b[i];

        /* percorre a linha a partir do segundo coeficiente */
        /* subtraindo as multiplicações (coeficiente * variavel) */
        for (int j = i+1; j < n; ++j)
            x[i] -= A[i][j] * x[j];

        /* divide pelo valor que ta multiplicando a variavel, descobrindo seu valor */
        x[i] /= A[i][i];
    }
}

/* Seja um Sistema Linear de ordem n */
/* Matriz de coeficientes A, Vetor de termos independentes B */
void eliminacaoGauss(double** A, double* b, int n){

    /* para cada uma das colunas, vai zerar tudo que ta abaixo do pivô */
    for(int i=0; i < n; ++i){

        /* faz o pivoteamento parcial */
        uint iPivo = encontraMax(A, i, n);
        if (i != iPivo)
            trocaLinhas(A, b, i, iPivo);
        
        /* para cada linha abaixo do pivô, vai zerar o coeficiente */
        for(int k=i+1; k < n; ++k){

            /* calcula o multiplicador, e zera */
            double m = A[k][i] / A[i][i];
            A[k][i] = 0.0;

            /* para cada elemento restante da linha, atualiza os coeficientes */
            for(int j=i+1; j < n; ++j)
                A[k][j] -= A[i][j] * m;

            /* atualiza o termo independente */
            b[k] -= b[i] * m;
        }
    }
}

// Aqui vai o código do EP02: Funções pra fazer a eliminação de Gauss