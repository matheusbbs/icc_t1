//Nome: Felipe Augusto Dittert Noleto; GRR:20205689
//Nome: Matheus Branco Barreto dos Santos; GRR:20203906

// Imprime o sistema
void imprime_sistema(intervalo **matriz, intervalo *vetorB, int tamanho);

// imprime o vetor das variáveis X
void imprime_resultado(intervalo *vetorX, int tamanho);

// imprime o resíduo percorrendo as linhas e colunas da matriz
void imprime_residuo(intervalo **matriz, intervalo *vetorB, intervalo *vetorX, int tamanho);

/* encontra o valor máximo (em módulo) de uma coluna i da matriz
retorna a linha que contém o valor máximo */
uint encontraMax(intervalo **matriz, uint i, uint tamanho);

/* Troca as linhas i, iPivo da matriz A e do vetor B */
void trocaLinhas(intervalo **matriz, intervalo *vetorB, int i, int iPivo);

/* Matriz de coeficientes A, Vetor de termos independentes B, valor das variaveis X */
void retrossubs(intervalo **matriz, intervalo *vetorB, intervalo *vetorX, int tamanho);

/* Matriz de coeficientes A, Vetor de termos independentes B */
/* Traingulariza um sistema a matriz usando eliminacao de Gauss*/
void eliminacaoGauss(intervalo **matriz, intervalo *vetorB, int tamanho);