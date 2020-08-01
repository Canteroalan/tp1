#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>


#define MAX 256

char **split(const char * s, const int * anchos, size_t ncampos);
void destruir_lineas(char **lineas, size_t n);
void imprimir_lineas(char **ss, size_t n);



char **split(const char *s, const int *anchos, size_t ncampos){

    size_t recorrido = 0;

    char **ss = malloc(sizeof(char *) * ncampos);
    if(ss == NULL){
    	free(ss);
        return NULL;
    }

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



bool leer_sintetizador(FILE *s, int n, int *f, float *a){
	
	char *q = malloc(sizeof(char) * MAX);
	if(q == NULL){
		free(q);
		return false;
	}

	int anchos_fa[3] = {1, 1, 8};

    char **ss = malloc(sizeof(char *) * MAX);
    if(ss == NULL){
    	free(ss);
    	free(q);
        return false;
    }

	//n = atoi(fgets(q, MAX, s));
	//printf("%d\n", n);

	int mult = 10;

	for(size_t i = 0; i < n; i++){
		fgets(q, MAX, s);
		
		if((f[i - 1] + 1) / mult != 0){
			anchos_fa[0]++;
			mult *= 10;
		}
		
		ss = split(q, anchos_fa, 3);
		f[i] = atoi(ss[0]);
		a[i] = atof(ss[2]);
		//printf("%d %f\n", f[i], a[i]);
	}


	/*for(size_t i = 0; i < 3; i++){
		fgets(q, MAX, s);
		printf("%s", q);
	}*/

	free(q);
	destruir_lineas(ss, 3);
	
	return true;
}


int main(int argc, char *argv[]){

	FILE *s = fopen(argv[1], "r");
	if(s == NULL){
		fclose(s);
		return 1;
	}

	char *q = malloc(sizeof(char) * MAX);
	if(q == NULL){
		free(q);
		fclose(s);
		return 1;
	}

	int n = atoi(fgets(q, MAX, s));
	
	int *f = malloc(sizeof(int) * n);
	if(f == NULL){
		free(f);
		free(q);
		fclose(s);
		return 1;
	}

	float *a = malloc(sizeof(float) * n);
	if(a == NULL){
		free(f);
		free(a);
		free(q);
		fclose(s);
		return 1;
	}

	if(! leer_sintetizador(s, n, f, a)){
		fclose(s);
		free(a);
		free(f);
		free(q);
		return 1;
	}

	printf("%d\n", n);

	for(size_t i = 0; i < n; i++)
		printf("%d %f\n", f[i], a[i]);

	fclose(s);
	free(f);
	free(a);
	free(q);

	return 0;
}