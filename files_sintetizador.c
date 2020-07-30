#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX 256

typedef struct {
	float * armonicos [2];
	size_t cantidad_armonicos;
	char * func_modulacion[3];
	float * parametros_modulacion[3];
} archivo_de_sint_t;




archivo_de_sint_t *leer_archivo_de_sintetizador(FILE * r, archivo_de_sint_t * t){
	char s[MAX];
	size_t n = atoi(fgets(s, MAX, r));
	float *multiplicador = malloc(n * sizeof(float));

	if(multiplicador == NULL)
		return NULL;

	float * intensidad = malloc(n * sizeof(float));

	if(intensidad == NULL)
		return NULL;

	for(size_t i = 0; i < n; i++){
		intensidad[i] = i + 1;
		char s[20];



	}




