PROGRAM=tp1
CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -g
LDFLAGS=-lm

all: $(PROGRAM)

$(PROGRAM): tp1.o argumentos.o
	$(CC) $(CFLAGS) $(LDFLAGS) tp1.o argumentos.o -o $(PROGRAM)

tp1.o: tp1.c ARGUMENTOS.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c tp1.c 

argumentos.o: argumentos.c ARGUMENTOS.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c argumentos.c