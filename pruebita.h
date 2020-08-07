#ifndef PRUEBITA_H
#define PRUEBITA_H

#include<stdio.h>
#include<stdlib.h>

typedef struct {
        float *frecuencia;
	float *intensidad;
        size_t cantidad_armonicos;
        char *func_mod[3];
        float  parametros[3][3];
} synt_t;


synt_t * crear_synt_t(size_t n);

float leer_intensidad(char *s);

char * leer_func_mod(char *s,size_t * j);

void leer_parametros(char *s,size_t p,float *v);

void destruir_synt_t(synt_t * r);

synt_t *leer_archivo_de_sintetizador(FILE *r);

#endif //PRUEBITA_H
