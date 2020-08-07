#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "TRAMO.H"
#include "NOTA.H"
#include "FUNCIONES.H"
#include "SINTETIZADOR.H"


#define PI 3.141592653589793
#define FASE 0
#define MAX_VALOR 32767 
#define MIN_VALOR 32768


struct _tramo {
    float *v;
    size_t n;
    double t0;
    int f_m;
};


//EJ3

double onda(double t, float a, float f, float phi){
    return  a * sin(2 * PI * f * t + phi);
}

void inicializar_muestras(float v[], size_t n){
    for(size_t i = 0; i < n; i++)
        v[i] = 0;
}
/*
void imprimir_muestras(const float v[], size_t n, double t0, int f_m){
 
    for(size_t i = 0; i < n;i++)
        double t = t0 + (double) i / f_m;
}*/

void muestrear_senoidal(float v[], size_t n, double t0, int f_m, float f, float a){

    for(int i = 0; i < n; i++){
       double t = t0 + (double) i / f_m;
        v[i] += onda(t, a, f, FASE);
    }
}

void muestrear_armonicos(float v[], size_t n, double t0, int f_m, float f, float a, float fa[][2], size_t n_fa){
    float frecuencia;
    float amplitud;

    inicializar_muestras(v,n);
        
    for(size_t i = 0; i < n_fa; i++){
        frecuencia = f * fa[i][0];
        amplitud = a * fa[i][1];
        muestrear_senoidal(v, n, t0, f_m, frecuencia, amplitud);
    }
}

tramo_t *_tramo_crear(double t0, double tf, int f_m){
    int n = f_m * (tf - t0);

    tramo_t *tramo = malloc(sizeof(tramo_t));
    if(tramo == NULL){
        printf("fallo en el malloc de _tramo_crear\n");
        return NULL;
    }

    float *muestras = malloc(n * sizeof(float));
    if(muestras == NULL){
        printf("fallo en el malloc de muestras\n");
        free(tramo);
        return NULL;
    }

	tramo_t r={muestras, n, t0, f_m};
    *tramo=r;

    return tramo;
}

void tramo_destruir(tramo_t *t){
    free(t->v);
    free(t);
}

tramo_t *tramo_clonar(const tramo_t *t){
    double t_f = (t->t0) + (double)(t->n) / (t->f_m);
        
    tramo_t *clon = _tramo_crear(t->t0, t_f, t->f_m);
    if(clon == NULL)
    	return NULL;

    for(size_t i=0;i<t->n;i++)
        clon->v[i]=t->v[i];

    return clon;
}

tramo_t *tramo_crear_muestreo(double t0, double tf, int f_m, float f, float a, float fa[][2], size_t n_fa){
    tramo_t *muestreo = _tramo_crear(t0, tf, f_m);
    if(muestreo == NULL)
    	return NULL;

    muestrear_armonicos(muestreo->v, muestreo->n, t0, f_m, f, a, fa, n_fa);
    
    return muestreo;
}

bool tramo_redimensionar(tramo_t *t, double tf){
    int new_n = (t->f_m) * (tf - (t->t0));

    float *aux = realloc((t->v), new_n * sizeof(float));
    if(aux==NULL)
        return false;

    t->v = aux;

    if((t->n) < new_n){
        for(size_t i = (t->n); i < new_n; i++)
            aux[i] = 0;
    }

    t->n=new_n;

    return true;
}

bool tramo_extender(tramo_t *destino, const tramo_t *extension){
    if((destino->t0 > extension->t0))
        return false;

    double tf_dest = (destino->t0) + (double)(destino->n) / (destino->f_m);
    double tf_exts = (extension->t0) + (double)(extension->n) / (extension->f_m);

    if(tf_dest < tf_exts)
        if(! tramo_redimensionar(destino, tf_exts))
        	return false;

    for(size_t i = 0; i < (destino->n); i++)
        if(i > (extension->t0 * extension->f_m) && i < (tf_exts * extension->f_m))
            destino->v[i]  =  destino->v[i] + extension->v[(i - (int)(extension->t0 * extension->f_m))];

    return true;
}



//TRAMO

double calcular_tf(note_t nota, synt_t *s){ 
	return nota.t0 + nota.duracion + s->parametros[2][0];
}

void determina_max_and_min(float *max, float *min, float v){  
	if(v > *max)
		*max = v;

	if(v < *min)
		*min = v;
}

tramo_t *modulacion(tramo_t *t, synt_t *s, float *h, float *l){
   	size_t n_ataque = t->f_m * s->parametros[0][0];
   	size_t n_sostenido = t->f_m * s->parametros[1][0] + n_ataque;
	float max = 0;
	float min = 0;

	for(size_t i = 0; i < t->n; i++){
		double tiempo = t->t0 + (double) i / t->f_m;

		if(i < n_ataque){
			t->v[i] = t->v[i] * modula_funcion(s->func_mod[0], s->parametros[0], tiempo);
			determina_max_and_min(&max, &min, t->v[i]);
		}

        if(i > n_ataque && i < n_sostenido){
		t->v[i] = t->v[i] * modula_funcion(s->func_mod[1], s->parametros[1], tiempo);
		determina_max_and_min(&max,&min, t->v[i]);
		}

		if(i > n_sostenido && i < t->n){
        	t->v[i] = t->v[i] * modula_funcion(s->func_mod[2], s->parametros[2], tiempo);
			determina_max_and_min(&max,&min, t->v[i]);
		}

		t->v[i] = 0;
	}
    
    *h = max;
	*l = min;
    
    return t;
}


int16_t *sintetizar_cancion(FILE *midi, FILE *sintetizador, int f_m, size_t *cantidad, char canal, int pps){
	
	nota_contenedor_t *contenedor = crear_nota_contenedor_t(midi, canal, pps);
	if(contenedor == NULL)
		return NULL;

	synt_t *synt = crear_synt_t(sintetizador);
	if(synt == NULL){
		destruir_nota_contenedor_t(contenedor);
		return NULL;
	}

	float grand_max = 0; //aca se va  a guardar el valor mas grande de los maximos 
	float grand_min = 0; //aca se va  a guardar el valor mas chico de los minimos
	float max, min;


	float t[synt->cantidad_armonicos][2];

	for(size_t i = 0; i < synt->cantidad_armonicos; i++){
		t[i][0] = synt->frecuencia[i];
		t[i][1] = synt->intensidad[i];
	}

	tramo_t *destino = _tramo_crear(0, 0, f_m);
	if(destino == NULL){
		destruir_nota_contenedor_t(contenedor);
		destruir_synt_t(synt);
		return NULL;
	}
	
	for(size_t i = 0; i < contenedor->cant_notas; i++){
		float f = leer_frecuencia_nota(contenedor->notes[i]);
		double tf = calcular_tf(contenedor->notes[i], synt);

		tramo_t *muestrea_nota = tramo_crear_muestreo(contenedor->notes[i].t0, tf, f_m, f, contenedor->notes[i].intensidad, t, synt->cantidad_armonicos);
		if(muestrea_nota == NULL){
			destruir_nota_contenedor_t(contenedor);
			destruir_synt_t(synt);
			tramo_destruir(destino);
			return NULL;
		}

		tramo_t *muestra_modulada = modulacion(muestrea_nota, synt, &max, &min);

		if(max > grand_max)                                              
			grand_max = max;

		if(min < grand_min)
			grand_min = min;

		if(! tramo_extender(destino, muestra_modulada)){
			destruir_nota_contenedor_t(contenedor);
			destruir_synt_t(synt);
			tramo_destruir(muestrea_nota);
			tramo_destruir(destino);
			return NULL;
		}

		tramo_destruir(muestrea_nota);
		tramo_destruir(muestra_modulada);
	}

	destruir_nota_contenedor_t(contenedor);
	destruir_synt_t(synt);

	int16_t *vect_wave = crear_muestras(destino, crear_factor_escala(grand_max,grand_min), cantidad);
	if(vect_wave == NULL){
		tramo_destruir(destino);
		return NULL;
	}

	tramo_destruir(destino);

	return vect_wave;
}

float crear_factor_escala(float maximo, float minimo){
	float a = MAX_VALOR / maximo;
	float b = MIN_VALOR / minimo;
	
	if(a > b)
		return a;
	
	return fabs(b);
}

int16_t *crear_muestras(tramo_t *t, float v, size_t *n){
	
	int16_t *vect_wave = malloc(t->n * sizeof(int16_t));
	if(vect_wave == NULL)
		return NULL;

	for(size_t i = 0; i < t->n; i++)
		vect_wave[i] = t->v[i] * v;
	
	*n = t->n;

	return vect_wave;
}

void destruir_int16_t(int16_t *v){
	free(v);
}


