#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 256

typedef struct {
	float *multiplicador;
	float *intensidad;
	size_t cantidad_armonicos;
	char *func_mod[3];
	float parametros[3][3];
} dato_t;

dato_t *crear_dato_t(size_t n){
	dato_t *nuevo_dato = malloc(sizeof(dato_t));

	if(nuevo_dato == NULL)
		return NULL;

	float *a = malloc(n * sizeof(float));

	if(a == NULL)
		return NULL;

	float *b = malloc(n * sizeof(float));

	if(b == NULL)
		return NULL;

	nuevo_dato->multiplicador = a;
	nuevo_dato->intensidad = b;
	nuevo_dato->cantidad_armonicos = n;

	//Creo que falta pedir memoria para func_mod.
	//float **c = malloc(sizeof(char *) * 3).

	return nuevo_dato;
}

void destruir_dato_t(dato_t * r){
	free(r->multiplicador);
	free(r->intensidad);
	free(r);
}

char **_leer_func_mod(char *s, size_t *p){
    int contador = 0;
    for(size_t i = 0; s[i]; i++)
        if(s[i] == ' ')
            contador++;
    char **vector = malloc((contador + 1) * sizeof(char *));

    if (vector == NULL)
        return NULL;

    size_t n=0;
    for(size_t i=0;i<(contador+1);i++){
    	    char* cadenas=malloc(15*sizeof(char));

	    if(cadenas == NULL){
		    free(vector);
		    return NULL;
	    }

	    vector[i]=cadenas;
	    for(size_t j = 0; (s[(j + n)] != ' ') && (s[(j + n)] != '\n'); j++)
		    vector[i][j] = s[(j + n)];
            n += (strlen(vector[i])) + 1;
    }
    *p = contador + 1;
    return vector;
}

void destruir_cadena(char** t,size_t n){
	for(size_t i=0;i<n;i++)
		free(t[i]);
	free(t);
}

dato_t *leer_archivo_de_sintetizador(FILE *r){
       	char s[MAX];
       	size_t n = atoi(fgets(s, MAX, r));
       	dato_t * archivador = crear_dato_t(n);
	size_t t;
	for(size_t i = 0; i < n; i++){
	       	archivador->multiplicador[i] = i + 1;
		char aux1[MAX];
		char ** c = _leer_func_mod(fgets(aux1, MAX, r), &t);
		archivador->intensidad[i] = atof(c[1]);
		destruir_cadena(c,t);
	}
	char ** p;
	size_t cantidad_cadenas;
	for(size_t i = 0; i < 3; i++){
	       	char aux2[MAX];
	        p=_leer_func_mod(fgets(aux2,MAX,r),&cantidad_cadenas);
		archivador->func_mod[i]=p[0];
		if(cantidad_cadenas > 1)
			for(size_t j = 0; j < cantidad_cadenas - 1; j++){
				archivador->parametros[j][i] = atof(p[j + 1]);
			}
		destruir_cadena(p,cantidad_cadenas);
	}
	return archivador;
}

int main(){
	FILE *p = fopen("sintetizador.txt","rt");

	if(p == NULL)
		return 1;

	dato_t *s = leer_archivo_de_sintetizador(p);
	printf("%ld\n",s->cantidad_armonicos);
	for(int j = 0;j < s->cantidad_armonicos; j++)
		printf("%f  %f\n", s->multiplicador[j], s->intensidad[j]);

	for(size_t i = 0; i < 3; i++){
		printf("%s ", s->func_mod[i]);

		for(size_t j = 0; j < 3; j++)
			printf("%f ", s->parametros[j][i]);
		
		printf("\n");
	}
	destruir_dato_t(s);
	fclose(p);
	return 0;
}

