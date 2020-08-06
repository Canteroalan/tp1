PROGRAM=tp1
CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -g
LDFLAGS=-lm

all: $(PROGRAM)

$(PROGRAM): tp1.o argumentos.o tramo.o nota.o ej5.o ej4.o sintetizador.o funciones_modulacion.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) tp1.o argumentos.o tramo.o nota.o ej5.o ej4.o sintetizador.o funciones_modulacion.o

tp1.o: tp1.c ARGUMENTOS.H TRAMO.H
	$(CC) $(CFLAGS) $(LDFLAGS) -c tp1.c 

argumentos.o: argumentos.c ARGUMENTOS.H
	$(CC) $(CFLAGS) $(LDFLAGS) -c argumentos.c

tramo.o: tramo.c TRAMO.H NOTA.H FUNCIONES.H SINTETIZADOR.H
	$(CC) $(CFLAGS) $(LDFLAGS) -c tramo.c

nota.o: nota.c NOTA.H
	$(CC) $(CFLAGS) $(LDFLAGS) -c nota.c

ej5.o: ej5.c NOTA.H
	$(CC) $(CFLAGS) $(LDFLAGS) -c ej5.c

ej4.o: ej4.c NOTA.H
	$(CC) $(CFLAGS) $(LDFLAGS) -c ej4.c

sintetizador.o: sintetizador.c SINTETIZADOR.H
	$(CC) $(CFLAGS) $(LDFLAGS) -c sintetizador.c

funciones_modulacion.o: funciones_modulacion.c FUNCIONES.H
	$(CC) $(CFLAGS) $(LDFLAGS) -c funciones_modulacion.c

