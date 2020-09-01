#ifndef SINTETIZADOR_H
#define SINTETIZADOR_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>


//TDA para almacenar los datos del archivo sintetizador.txt
typedef struct {
	float *frecuencia; //Vector de frecuencias.
	float *intensidad; //Vector de intensidad.
	size_t cantidad_armonicos; //Cantidad de frecuencias e intensidades.
	char *func_mod[3]; //Vector con 3 funciones de modulacion.
	float parametros[3][3]; //Matriz con parametros de las funciones de modulacion
}synt_t;


//sintetizador.c
synt_t *crear_synt_t(FILE *s);
void destruir_synt_t(synt_t *synt);
char **split(const char *s, const int *anchos, size_t ncampos);
void destruir_lineas(char **lineas, size_t n);
bool leer_sintetizador(FILE *s, synt_t *synt);
bool leer_func_mod(char *s, char *func_mod, float parametros[3]);
void generar_matriz_armonicos(synt_t *synt, float matriz[][2]);

#endif
