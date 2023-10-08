#Nome: Felipe Augusto Dittert Noleto; GRR:20205689
#Nome: Matheus Branco Barreto dos Santos; GRR:20203906

CFLAGS = -g -c -Wall -O3 -mavx -march=native  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = main.o analise_intervalar.o  metodo_minquad.o eliminacao_gauss.o 
     
all: main.o analise_intervalar.o  metodo_minquad.o eliminacao_gauss.o
	$(CC) -o ajustePol main.o analise_intervalar.o  metodo_minquad.o eliminacao_gauss.o $(LDFLAGS)

analise_intervalar.o: analise_intervalar.c
	$(CC) -c $(CFLAGS) analise_intervalar.c

metodo_minquad.o: metodo_minquad.c
	$(CC) -c $(CFLAGS) metodo_minquad.c

eliminacao_gauss.o: eliminacao_gauss.c
	$(CC) -c $(CFLAGS) eliminacao_gauss.c

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f $(objects) ajustePol