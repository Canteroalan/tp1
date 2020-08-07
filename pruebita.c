#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"pruebita.h"

#define MAX 256

synt_t * crear_synt_t(size_t n){
	synt_t * t=malloc(sizeof(synt_t));

	if(t == NULL)
		return NULL;

        t->frecuencia=malloc(n*sizeof(float));

	if(t->frecuencia == NULL){
		free(t);
		return NULL;
	}

	t->intensidad=malloc(n*sizeof(float));

	if(t->intensidad == NULL){
		free(t->frecuencia);
		free(t);
		return NULL;
	}
	return t;
}

float leer_intensidad(char *s){
	size_t i;
	for(i=0;!(s[i] == ' ');i++);
	char r [MAX];
	for(size_t j=0;!(s[j+i] =='\n');j++)
		r[j]=s[j+i];
	return atof(r);
}

char * leer_func_mod(char *s,size_t * j){
	char r[MAX];
	int i;
	for(i=0;(!(s[i] == ' ')) &&(!(s[i] == '\n'));i++)
		r[i]=s[i];
	r[i]='\0';
	*j=i+1;
	int n=strlen(r);
	char * copia=malloc((n+1)*sizeof(char));

	if(copia == NULL)
		return NULL;

	return memcpy(copia,r,n);
}

void leer_parametros(char *s,size_t p,float *v){
	int contador=0;
	for(size_t i=p;s[i];i++){
		if(s[i]==' ')
			contador++;
	}
	size_t n=0;
	for(size_t i=0;i<contador+1;i++){
		char r[MAX];
		size_t j;
		for(j=0;(!(s[j+p+n]==' '))&&(!(s[j+p+n]=='\0'));j++)
			r[j]=s[j+p+n];
		r[j]='\0';
		v[i]=atof(r);
		n+=j+1;
	}
}

void destruir_synt_t(synt_t * r){
	free(r->frecuencia);
	free(r->intensidad);
	for(size_t i=0;i<3;i++)
		free(r->func_mod[i]);
	free(r);
}

synt_t *leer_archivo_de_sintetizador(FILE *r){
       	char s[MAX];
       	size_t n = atoi(fgets(s, MAX, r));
	synt_t * archivador=crear_synt_t(n);

	if(archivador == NULL)
		return NULL;
		
	for(size_t i=0;i<n;i++){
		archivador->frecuencia[i]=(i+1);
		char aux[MAX];
		archivador->intensidad[i]=leer_intensidad(fgets(aux,MAX,r));
	}
	archivador->cantidad_armonicos=n;
	for(size_t i=0;i<3;i++){
		char aux[MAX];
		size_t t;
		archivador->func_mod[i]=leer_func_mod(fgets(aux,MAX,r),&t);
		leer_parametros(aux,t,archivador->parametros[i]);
	}
	return archivador;
}
				

