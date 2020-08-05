#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "TRAMO.H"
#include "FUNCIONES.H"
#include "SINTETIZADOR.H"
#include "NOTA.H"




float leer_frecuencia_tramo(note_t *nota){
	int i;

	for(i = 0; i < 12; i++)
		if(! strcmp(nota->nota, notas[i]))
			break;

	return 440 * (pow((1.0) / 2, 4 - nota->octava)) * (pow(2, (i - 9) / 12));
}

double calcular_tf(note_t *nota, float td){ 
	return nota->t0 + nota->duracion + td;
}

float **generar_matriz_armonicos(synt_t synt){

	float **armonicos = malloc(2 * sizeof(float *));
	if(armonicos == NULL)
		return NULL;

	for(size_t i = 0; i < 2; i++){

		float *almacenador = malloc(synt->cantidad_armonicos * sizeof(float));
		if(almacenador == NULL){
			free(armonicos);
			return NULL;
		}

		armonicos[i] = almacenador;
	}

	for(size_t j = 0; j < synt->cant_armonicos; j++){
		armonicos [j][0] = synt->frecuencia[j];
		armonicos [j][1] = synt->intensidad[j];
	}

	return armonicos;
}

void destruir_matriz(float **r, size_t cantidad_de_columnas){
	for(size_t i = 0; i < cantidad_de_columnas; i++)
		free(r[i]);
	
	free(r);
}

tramo_t  * modulacion(tramo_t *t, synt_t *p,){
       	size_t n_ataque = t->f_m * p->parametros[0][0];
       	size_t n_sostenido = t->f_m * p->parametros[0][1] + n_ataque;
	for(size_t i = 0; i < t->n; i++){
		double tiempo=t->t0 +(double)i/t->f_m;
		if(i < n_ataque)
			t->v[i] = t->v[i] * modula_funcion(p->func_mod[0],p->parametros[0],tiempo);
	        if(i>n_ataque && i < n_sostenido)
			t->v[i] = t->v[i] * modula_funcion(p->func_mod[1],p->parametros[1],tiempo);
                t->v[i] = t->v[i] * modula_funcion(p->func_mod[2],p->parametros[2],tiempo);
	}
        return t;
}

tramo_t *sintetizar_cancion(note_t v[],size_t tamagno,synt_t * w ,int fre_mtro){
	float ** t=genera_matriz_armonicos(w);
	for(size_t i=0;i<tamagno;i++){
		float p=leer_frecuencia_tramo(v[i]);
		double tf=_calcula_tf(v[i]->t0,v[i]->duracion,w->parametros[0][3]);
		tramo_t * muestrea_nota=tramo_crear_muestreo(v[i]->t0,tf,fre_mtro,p,v[i]->intensidad,t,w->cantidad_armonicos);
		tramo_t * muestra_modulada=(muestrea_nota,w);

	}
	destruir_matriz(t);
	return el tramo con todas las notas sumadas!;
}

// me quedo por pensar como escalar el tramo para pasarselo al wave , espero que se entienda todo lo anterior 



