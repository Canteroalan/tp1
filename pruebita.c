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

	float*a = malloc(n * sizeof(float));
	float*b = malloc(n * sizeof(float));

	nuevo_dato->multiplicador = a;
	nuevo_dato->intensidad = b;
	nuevo_dato->cantidad_armonicos = n;

	return nuevo_dato;
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
	    if(cadenas == NULL)
    	    return NULL;

    	vector[i]=cadenas;

    	for(size_t j = 0; (s[(j + n)] != ' ') && (s[(j + n)] != '\0'); j++)
            vector[i][j] = s[(j + n)];

        n += (strlen(vector[i])) + 1;
	}

    *p = contador + 1;

    return vector;
}

void destruir_cadena(char **t, size_t n){
	for(size_t i = 0; i < n; i++)
		free(t[i]);
	
	free(t);
}


dato_t *leer_archivo_de_sintetizador(FILE *r){
    char s[MAX];
    size_t n = atoi(fgets(s, MAX, r)); //aca lei el primer numero (esto iria en cantidad_armonicos)
	printf("%ld\n",n);

	dato_t * archivador = crear_dato_t(n);

    for(size_t i = 0; i < n; i++){ //en esta parte se leen los multiplicadores y las intensidades 
        archivador->multiplicador[i] = i + 1;
		char aux[MAX];
		size_t t;
		char **c = _leer_func_mod(fgets(aux, MAX, r), &t);
		archivador->intensidad[i] = atof(c[1]);
    }

	for(size_t i = 0; i < 3; i++){
        char aux[MAX];
        size_t cantidad_cadenas;

        char ** p=_leer_func_mod(fgets(aux,MAX,r),&cantidad_cadenas);
		archivador->func_mod[i]=p[0];

		if(cantidad_cadenas > 1)
			for(size_t j = 0; j < cantidad_cadenas - 1; j++)
				archivador->parametros[j][i] = atof(p[j + 1]);
	}

	return archivador;
}

int main(){
	FILE *p = fopen("sintetizador.txt","rt");

	if(p == NULL)
		return 1;

	dato_t *s = leer_archivo_de_sintetizador(p);
	for(int j = 0;j < s->cantidad_armonicos; j++)
		printf("%f  %f\n", s->multiplicador[j], s->intensidad[j]);

	for(size_t i = 0; i < 3; i++){
		printf("%s ", s->func_mod[i]);

		for(size_t j = 0; j < 3; j++)
			printf("%f ", s->parametros[j][i]);
		
		printf("\n");
	}

	fclose(p);

	return 0;
}

