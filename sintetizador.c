#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>


#include "SINTETIZADOR.H"


#define MAX 256

synt_t *crear_synt_t(FILE *s){

	synt_t *synt = malloc(sizeof(synt_t));
	if(synt == NULL)
		return NULL;

	char *q = malloc(sizeof(char) * MAX);
	if(q == NULL)
		return false;

	synt->cantidad_armonicos = atoi(fgets(q, MAX, s));

	synt->frecuencia = malloc(synt->cantidad_armonicos * sizeof(float));
	if(synt->frecuencia == NULL)
		return NULL;

	synt->intensidad = malloc(synt->cantidad_armonicos * sizeof(float));
	if(synt->intensidad == NULL)
		return NULL;


	for(size_t i = 0; i < 3; i++){
		synt->func_mod[i] = malloc(sizeof(char) * 15);
		if(synt->func_mod[i] == NULL)
			return NULL;
	}

	for(size_t i = 0; i < 3; i++)
		for(size_t j = 0; j < 3; j++)
			synt->parametros[i][j] = 0;

	if(! leer_sintetizador(s, synt)){
		destruir_synt_t(synt);
		free(q);
		return NULL;
	}

	free(q);

	return synt;
}

void destruir_synt_t(synt_t *synt){
	free(synt->frecuencia);
	free(synt->intensidad);

	for(size_t i = 0; i < 3; i++)
		free(synt->func_mod[i]);

	free(synt);
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


bool leer_sintetizador(FILE *s, synt_t *synt){
	
	char *q = malloc(sizeof(char) * MAX);
	if(q == NULL)
		return false;

	int anchos_fa[3] = {1, 1, 8};

	//int mult = 10;

	for(size_t i = 0; i < synt->cantidad_armonicos; i++){
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

		synt->frecuencia[i] = atof(ss[0]);
		synt->intensidad[i] = atof(ss[2]);

		destruir_lineas(ss, 3);
	}

	for(size_t i = 0; i < 3; i++){
		fgets(q, MAX, s);
		leer_func_mod(q, synt->func_mod[i], synt->parametros[i]);
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
    		size_t j;
    		for(j = 0; s[j] != ' '; j++)
    			func_mod[j] = s[j];

    		n += (j + 1);
    	}

    	for(size_t i = 0; i < 8; i++)
    		vector[i] = 0;

    	size_t a;

	    for(a = 0; (s[(a + n)] != ' ') && (s[(a + n)] != '\n'); a++)
		    vector[a] = s[a + n];

		parametros[i] = atof(vector);

        n += (a + 1);
    }

    return true;
}

/*void imprimir_synt_t(synt_t *synt){

	printf("%ld\n", synt->cantidad_armonicos);

	for(size_t i = 0; i < synt->cantidad_armonicos; i++)
		printf("%f %f\n", synt->frecuencia[i], synt->intensidad[i]);

	for(size_t i = 0; i < 3; i++){
		printf("%s ", synt->func_mod[i]);

		for(size_t j = 0; j < 3; j++)
			printf("%f ", synt->parametros[i][j]);

		printf("\n");
	}
}*/
