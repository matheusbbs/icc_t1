#Nome: Felipe Augusto Dittert Noleto; GRR:20205689
#Nome: Matheus Branco Barreto dos Santos; GRR:20203906

LIKWID_HOME = /home/soft/likwid
CFLAGS = -g -c -Wall -fopt-info-vec -fopt-info-vec-missed -falign-functions=32 -falign-loops=32 -O3 -mavx -march=native -DLIKWID_PERFMON -I$(LIKWID_HOME)/include # flags de compilacao
LDFLAGS = -lm -L${LIKWID_HOME}/lib -llikwid

CC = gcc

# arquivos-objeto
	objects = main.o analise_intervalar.o  metodo_minquad.o eliminacao_gauss.o 
     
all: main.o analise_intervalar.o  metodo_minquad.o eliminacao_gauss.o gera_entrada.c
	$(CC) -o ajustePol main.o analise_intervalar.o  metodo_minquad.o eliminacao_gauss.o $(LDFLAGS)
	$(CC) gera_entrada.c -o gera_entrada

analise_intervalar.o: analise_intervalar.c
	$(CC) -c $(CFLAGS) analise_intervalar.c

metodo_minquad.o: metodo_minquad.c
	$(CC) -c $(CFLAGS) metodo_minquad.c

eliminacao_gauss.o: eliminacao_gauss.c
	$(CC) -c $(CFLAGS) eliminacao_gauss.c

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f $(objects) ajustePol gera_entrada
