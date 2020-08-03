PROGRAM=tp1
CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -g
LDFLAGS=-lm

all: $(PROGRAM)

$(PROGRAM): tp1.o argumentos.o nota.o ej5.o ej4.o
	$(CC) $(CFLAGS) $(LDFLAGS) tp1.o argumentos.o nota.o ej5.o ej4.o -o $(PROGRAM)

tp1.o: tp1.c ARGUMENTOS.H NOTA.H
	$(CC) $(CFLAGS) $(LDFLAGS) -c tp1.c 

argumentos.o: argumentos.c ARGUMENTOS.H
	$(CC) $(CFLAGS) $(LDFLAGS) -c argumentos.c

nota.o: nota.c NOTA.H
	$(CC) $(CFLAGS) $(LDFLAGS) -c nota.c

ej5.o: ej5.c NOTA.H
	$(CC) $(CFLAGS) $(LDFLAGS) -c ej5.c

ej4.o: ej4.c NOTA.H
	$(CC) $(CFLAGS) $(LDFLAGS) -c ej4.c