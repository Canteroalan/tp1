#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>


#define MAX 256


typedef struct {
	int *frecuencia;
	float *intensidad;
	int cantidad_armonicos;
	char *func_mod[3];
	float parametros[3][3];
} dato_t;


dato_t *crear_dato_t(FILE *s);
void destruir_dato_t(dato_t *d);
char **split(const char * s, const int * anchos, size_t ncampos);
void destruir_lineas(char **lineas, size_t n);
void imprimir_lineas(char **ss, size_t n);
bool leer_sintetizador(FILE *s, int n, int *f, float *a, char *func_mod[3], float parametros[3][3]);
bool leer_func_mod(char *s, char *func_mod, float parametros[3]);


dato_t *crear_dato_t(FILE *s){

	dato_t *d = malloc(sizeof(dato_t));
	if(d == NULL)
		return NULL;

	char *q = malloc(sizeof(char) * MAX);
	if(q == NULL)
		return false;

	d->cantidad_armonicos = atoi(fgets(q, MAX, s));

	d->frecuencia = malloc(d->cantidad_armonicos * sizeof(int));
	if(d->frecuencia == NULL)
		return NULL;

	d->intensidad = malloc(d->cantidad_armonicos * sizeof(float));
	if(d->intensidad == NULL)
		return NULL;


	for(size_t i = 0; i < 3; i++){
		
		d->func_mod[i] = malloc(sizeof(char) * 15);
		if(d->func_mod[i] == NULL)
			return NULL;
	}

	free(q);

	return d;
}

void destruir_dato_t(dato_t *d){
	free(d->frecuencia);
	free(d->intensidad);

	for(size_t i = 0; i < 3; i++)
		free(d->func_mod[i]);

	free(d);
}

char **split(const char *s, const int *anchos, size_t ncampos){

    size_t recorrido = 0;

    char **ss = malloc(sizeof(char *) * ncampos);
    if(ss == NULL)
        return NULL;

    for (size_t i = 0; i < ncampos; i++) {
        
        ss[i] = malloc(sizeof(char) * (anchos[i] + 1));
        if(ss[i] == NULL){
            destruir_lineas(ss, i);
            return NULL;
        }

        strncpy(ss[i], s + recorrido, anchos[i]);
        ss[i][anchos[i]] = '\0';
        recorrido += anchos[i];
    }

    return ss;
}

void destruir_lineas(char **lineas, size_t n){
    for(size_t i = 0; i < n; i++){
        free(lineas[i]);
    }

    free(lineas);
}

bool leer_sintetizador(FILE *s, int n, int *f, float *a, char *func_mod[3], float parametros[3][3]){
	
	char *q = malloc(sizeof(char) * MAX);
	if(q == NULL)
		return false;

	int anchos_fa[3] = {1, 1, 8};

	//int mult = 10;

	for(size_t i = 0; i < n; i++){
		fgets(q, MAX, s);
		
		//En caso de que la frecuencia supere 1 cifra.
		/*if(((f[i - 1] + 1) / mult) != 0){
			anchos_fa[0]++;
			mult *= 10;
		}*/
		
		char **ss = split(q, anchos_fa, 3);
		if(ss == NULL){
    		free(q);
        	return false;
    	}

		f[i] = atoi(ss[0]);
		a[i] = atof(ss[2]);

		destruir_lineas(ss, 3);
	}

	for(size_t i = 0; i < 3; i++){
		fgets(q, MAX, s);
		leer_func_mod(q, func_mod[i], parametros[i]);
	}

	free(q);

	return true;
}

bool leer_func_mod(char *s, char *func_mod, float parametros[3]){
	int contador = 1;
    
    for(size_t i = 0; s[i] != '\n'; i++)
        if(s[i] == ' ')
        	contador++;

    if(contador == 1){
    	for(size_t j = 0; s[j] != '\n'; j++)
    			func_mod[j] = s[j];

    	for(size_t i = 0; i < 3; i++)
    		parametros[i] = 0;

    	return true;
    }

    char vector[8];

    size_t n = 0;

    for(size_t i = 0; i < (contador - 1); i++){

    	if(i == 0){
    		for(size_t j = 0; s[j] != ' '; j++)
    			func_mod[j] = s[j];

    		n += strlen(func_mod) + 1;
    	}

    	for(size_t i = 0; i < 8; i++)
    		vector[i] = 0;

    	size_t j;

	    for(j = 0; (s[(j + n)] != ' ') && (s[(j + n)] != '\n'); j++)
		    vector[j] = s[j + n];

		parametros[i] = atof(vector);

        n += (j + 1);
    }

    return true;
}


int main(int argc, char *argv[]){

	FILE *s = fopen(argv[1], "r");
	if(s == NULL){
		fclose(s);
		return 1;
	}

	dato_t *dato = crear_dato_t(s);
	if(dato == NULL){
		fclose(s);
		return 1;
	}

	if(! leer_sintetizador(s, dato->cantidad_armonicos, dato->frecuencia, dato->intensidad, dato->func_mod, dato->parametros)){
		destruir_dato_t(dato);
		fclose(s);
		return 1;
	}

	printf("%d\n", dato->cantidad_armonicos);

	for(size_t i = 0; i < dato->cantidad_armonicos; i++)
		printf("%d %f\n", dato->frecuencia[i], dato->intensidad[i]);

	for(size_t i = 0; i < 3; i++){
		printf("%s ", dato->func_mod[i]);

		for(size_t j = 0; j < 3; j++)
			printf("%f ", dato->parametros[i][j]);

		printf("\n");
	}


	destruir_dato_t(dato);
	fclose(s);

	return 0;
}