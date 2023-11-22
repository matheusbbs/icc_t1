//Nome: Felipe Augusto Dittert Noleto; GRR:20205689
//Nome: Matheus Branco Barreto dos Santos; GRR:20203906

// recebe matriz de intervalos, vetor B e seus tamanhos e os imprime
void imprime_sistema(intervalo **matriz, intervalo *vetorB, int tamanho);

// recebe matriz contínua de intervalos, vetor B e seus tamanhos e os imprime
void imprime_sistemaCont(intervalo *matriz, intervalo *vetorB, int tamanho);

// recebe vetor de intervalos e seu tamanho e os imprime
void imprime_vetor(intervalo *vetorX, int tamanho);

/* encontra o valor máximo (em módulo) de uma coluna i da matriz
retorna a linha que contém o valor máximo */
uint encontraMax(intervalo **matriz, uint i, uint tamanho);

/* encontra o valor máximo (em módulo) de uma coluna i da matriz contínua
retorna a linha que contém o valor máximo */
uint encontraMaxCont(intervalo *matriz, uint i, uint tamanho);

// Troca as linhas i, iPivo da matriz e do vetor B realizando o pivoteamento
void trocaLinhas(intervalo **matriz, intervalo *vetorB, int i, int iPivo);

// Troca as linhas i, iPivo da matriz contínua e do vetor B realizando o pivoteamento
void trocaLinhasCont(intervalo *matriz, intervalo *vetorB, int i, int iPivo);

// realiza a retrosubstituicao a partir de um sistema guardando o resultado em vetorX
void retrossubs(intervalo **matriz, intervalo *vetorB, intervalo *vetorX, int tamanho);

// realiza a retrosubstituicao a partir de um sistema (matriz continua) guardando o resultado em vetorX
void retrossubsCont(intervalo *matriz, intervalo *vetorB, intervalo *vetorX, int tamanho);

// Triangulariza um sistema de equacao a partir do metodo de Gauss
void eliminacaoGauss(intervalo **matriz, intervalo *vetorB, int tamanho);

// Triangulariza um sistema de equacao (matriz contínua) a partir do metodo de Gauss
void eliminacaoGaussCont(intervalo *matriz, intervalo *vetorB, int tamanho);