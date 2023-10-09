//Nome: Felipe Augusto Dittert Noleto; GRR:20205689
//Nome: Matheus Branco Barreto dos Santos; GRR:20203906

//intervalo, contem 2 doubles vizinhos em numero de maquina
struct intervaloStruct{
    double menor, maior;
}typedef intervalo;

//retorna numero de maquina seguinte ao numero passado
double proximo(double numero);

//retorna numero de maquina anterior ao numero passado
double anterior(double numero);

//encontra intervalo com dois numeros de maquina vizinhos
//que contem o numero solicitado a partier de um long double
void encontraIntervaloLongo(intervalo *inter, long double longo);

//encontra intervalo a partir de uma string
void encontraIntervalo(intervalo *inter, char entrada[]);

//imprime intervalo
void imprime(intervalo inter);

//soma dois intervalos, retorna resultado
intervalo somar(intervalo *inter, intervalo *inter2);

//subtrai dois intervalos, retorna resultado
intervalo subtrair(intervalo *inter, intervalo *inter2);

//multiplica dois intervalos, retorna resultado
intervalo multiplicar(intervalo *inter, intervalo *inter2);

//divide dois intervalos, retorna resultado
intervalo dividir(intervalo *inter, intervalo *inter2);

//eleva um intervalo a uma potencia >= 0 e retorna o resultado
//erro: retorna [-1,-1] caso p < 0
intervalo potencia(intervalo *inter, int p);