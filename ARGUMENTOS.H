#ifndef ARGUMENTOS
#define ARGUMENTOS

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>


void uso(char *argv[]);
FILE *abrir_sintetizador(int argc, char *argv[]);
FILE *abrir_midi(int argc, char *argv[]);
FILE *abrir_wave(int argc, char *argv[]);
char leer_canal(int argc, char *argv[]);
int leer_frecuencia(int argc, char *argv[]);
int leer_pulso(int argc, char *argv[]);


#endif
