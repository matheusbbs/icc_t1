// Imprime o sistema
void imprime_sistema(double** A, double* b, int n);

// imprime o vetor das variáveis X
void imprime_resultado(double *x, int tam);

// imprime o resíduo percorrendo as linhas e colunas da matriz
void imprime_residuo(double **matriz, double *vetor, double *x, int tam);

/* encontra o valor máximo (em módulo) de uma coluna i da matriz
retorna a linha que contém o valor máximo */
uint encontraMax(double** A, uint i, uint n);

/* Troca as linhas i, iPivo do Sistema */
void trocaLinhas(double** A, double* b, int i, int iPivo);

// função que calcula as variáveis X usando retrossubstituição
void retrossubs(double** A, double* b, double* x, int n);

// Eliminação de Gauss com pivoteamento parcial
void eliminacaoGauss(double** A, double* b, int n);