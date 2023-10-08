//Nome: Felipe Augusto Dittert Noleto; GRR:20205689
//Nome: Matheus Branco Barreto dos Santos; GRR:20203906

// Imprime o sistema
void imprime_sistema(double** A, double* b, int n);

// imprime o vetor das variáveis X
void imprime_resultado(double *x, int tam);

// imprime o resíduo percorrendo as linhas e colunas da matriz
void imprime_residuo(double **matriz, double *vetor, double *x, int tam);

/* encontra o valor máximo (em módulo) de uma coluna i da matriz
retorna a linha que contém o valor máximo */
uint encontraMax(double** A, uint i, uint n);

/* Troca as linhas i, iPivo da matriz A e do vetor B */
void trocaLinhas(double** A, double* b, int i, int iPivo);

/* Matriz de coeficientes A, Vetor de termos independentes B, valor das variaveis X */
void retrossubs(double** A, double* b, double* x, int n);

/* Matriz de coeficientes A, Vetor de termos independentes B */
/* Traingulariza um sistema a matriz usando eliminacao de Gauss*/
void eliminacaoGauss(double** A, double* b, int n);