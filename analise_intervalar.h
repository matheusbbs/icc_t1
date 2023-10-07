// Struct:

//intervalo, contem 2 doubles vizinhos em numero de maquina
struct intervaloStruct{
    double menor, maior;
}typedef intervalo;

//retorna numero de maquina seguinte ao numero passado
double proximo(double numero);

//retorna numero de maquina anterior ao numero passado
double anterior(double numero);

//encontra intervalo com dois numeros de maquina vizinhos
//que contem o numero solicitado
void encontraIntervalo(intervalo *inter, char entrada[]);

//imprime intervalo
void imprime(intervalo inter);

//soma dois intervalos, guarda resultado no segundo
void somar(intervalo *inter, intervalo *inter2);

//subtrai dois intervalos, guarda resultado no segundo
void subtrair(intervalo *inter, intervalo *inter2);

//multiplica dois intervalos, guarda resultado no segundo
void multiplicar(intervalo *inter, intervalo *inter2);

//divide dois intervalos, guarda resultado no segundo
void dividir(intervalo *inter, intervalo *inter2);

//eleva um intervalo a uma potencia >= 0
void potencia(intervalo *inter, int p);