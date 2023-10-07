CFLAGS = -Wall -std=c99 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = main.o analise_intervalar.o  metodo_minquad.o eliminacao_gauss.o 
     
main: main.o analise_intervalar.o  metodo_minquad.o eliminacao_gauss.o
	$(CC) -o main main.o analise_intervalar.o  metodo_minquad.o eliminacao_gauss.o $(LDFLAGS)

analise_intervalar.o: analise_intervalar.c
	$(CC) -c $(CFLAGS) analise_intervalar.c

metodo_minquad.o: metodo_minquad.c
	$(CC) -c $(CFLAGS) metodo_minquad.c

eliminacao_gauss.o: eliminacao_gauss.c
	$(CC) -c $(CFLAGS) eliminacao_gauss.c

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f $(objects) main
