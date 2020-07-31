#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX 256

typedef struct {
	float * armonicos [2];
	size_t cantidad_armonicos;
	char * func_modulacion[3];        //aca se guardan los nombres de las funciones de modulacion 
	float * parametros_modulacion[3]; //aca se guardan los parametros de modulacion 
} archivo_de_sint_t;


float _leer_intensidad(char * c){
	char r[MAX];
        for(int i=0;c[i];i++)
                r[i]=c[2+i];
        return atof(r);
}

char **_leer_func_mod(char *s,size_t *p){
	  int contador=0;
        for(size_t i=0;s[i];i++){
                if(s[i] == ' ')
                        contador++;
        }

        char ** vector=malloc((contador+1)*sizeof(char*));

        if (vector == NULL)
                return NULL;
        size_t n=0;

        for(size_t i=0;i<(contador+1);i++){
                char* cadenas=malloc(15*sizeof(char));

                if(cadenas == NULL)
                        return NULL;

                vector[i]=cadenas;

                for(size_t j=0;(s[(j+n)] !=' ') && (s[(j+n)] !='\0');j++){
                        vector[i][j]=s[(j+n)];
                }
                n+=(strlen(vector[i]))+1;
        }
        *p=contador+1;
        return vector;
}


archivo_de_sint_t *leer_archivo_de_sintetizador(FILE * r, archivo_de_sint_t * t){
	char s[MAX];
	size_t n = atoi(fgets(s, MAX, r));
	float *multiplicador = malloc(n * sizeof(float));

	if(multiplicador == NULL)
		return NULL;

	float * intensidad=malloc(n*sizeof(float));

	if(intensidad == NULL)
		return NULL;


	for(size_t i=0;i<n;i++){
		multiplicador[i]=i+1;
		char aux[MAX];
		intensidad[i]=_leer_intensidad(fgets(aux,MAX,r));
	}
	size_t cantidad_cadenas;
        for(int i=0;i<3;i++){
		//aca hay que usar la funcion leer_func_mod y guardar los vectores que da en sus correspondientes lugares 



				



	}
// esta destruye la estructura 
void destruir_archivo_de_sint_t (archivo_de_sint_t * t){
	for(size_t=0;i<3;i++){
		if(i<2)
			free(t->armonicos[i]);
		free(t->func_modulacion[i]);
		free(t->parametros_modulacion[i]);
	}
}





