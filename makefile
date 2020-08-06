PROGRAM=tp1
CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -g
LDFLAGS=-lm

all: $(PROGRAM)

$(PROGRAM): tp1.o argumentos.o tramo.o nota.o ej5.o ej4.o sintetizador.o funciones_modulacion.o
	$(CC) $(CFLAGS) -o $(PROGRAM) tp1.o argumentos.o tramo.o nota.o ej5.o ej4.o sintetizador.o funciones_modulacion.o $(LDFLAGS)

tp1.o: tp1.c ARGUMENTOS.H TRAMO.H
	$(CC) $(CFLAGS) -c tp1.c $(LDFLAGS)

argumentos.o: argumentos.c ARGUMENTOS.H
	$(CC) $(CFLAGS) -c argumentos.c $(LDFLAGS)

tramo.o: tramo.c TRAMO.H NOTA.H FUNCIONES.H SINTETIZADOR.H
	$(CC) $(CFLAGS) -c tramo.c $(LDFLAGS)

nota.o: nota.c NOTA.H
	$(CC) $(CFLAGS) -c nota.c $(LDFLAGS)

ej5.o: ej5.c NOTA.H
	$(CC) $(CFLAGS) -c ej5.c $(LDFLAGS)

ej4.o: ej4.c NOTA.H
	$(CC) $(CFLAGS) -c ej4.c $(LDFLAGS)

sintetizador.o: sintetizador.c SINTETIZADOR.H
	$(CC) $(CFLAGS) -c sintetizador.c $(LDFLAGS)

funciones_modulacion.o: funciones_modulacion.c FUNCIONES.H
	$(CC) $(CFLAGS) -c funciones_modulacion.c $(LDFLAGS)

