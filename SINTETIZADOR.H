#ifndef SINTETIZADOR
#define SINTETIZADOR

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>


typedef struct {
	float *frecuencia;
	float *intensidad;
	size_t cantidad_armonicos;
	char *func_mod[3];
	float parametros[3][3];
}synt_t;



//sintetizador.c
synt_t *crear_synt_t(FILE *s);
void destruir_synt_t(synt_t *synt);

char **split(const char * s, const int * anchos, size_t ncampos);
void destruir_lineas(char **lineas, size_t n);
void imprimir_lineas(char **ss, size_t n);

bool leer_sintetizador(FILE *s, synt_t *synt);
bool leer_func_mod(char *s, char *func_mod, float parametros[3]);

//void imprimir_synt_t(synt_t *synt);

float **generar_matriz_armonicos(synt_t *synt);
void destruir_matriz(float **r, size_t cantidad_de_columnas);

#endif
