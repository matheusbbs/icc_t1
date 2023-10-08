//Nome: Felipe Augusto Dittert Noleto; GRR:20205689
//Nome: Matheus Branco Barreto dos Santos; GRR:20203906

struct Ponto{ //guarda x e y de um ponto
    intervalo x, y;
}typedef ponto;

//le os pontos de stdin
void lerPontos(ponto *pontos, int qntPontos);

//preenche matriz com metodo dos minimos quadrados de forma nao otimizada
void preencherMatriz(intervalo **matriz, int tam, ponto *pontos, int qntPontos);

// preenche a matriz de maneira otimizada, calculando só as diagonais
void preencherMatrizOtimizado(intervalo **matriz, ponto *pontos, int qntPontos, int tam);

//preenche o vetor B pelo metodo dos minimos quadrados
void preencherVetor(intervalo *vetor, ponto *pontos, int qntPontos, int tam);

//calcula e imprime residuos entre tabela inicial e coeficientes calculados
void imprimeResiduoGauss(ponto *pontos, intervalo *coeficientes, int qntPontos, int grau);