#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "TRAMO.H"
#include "FUNCIONES.H"
#include "SINTETIZADOR.H"
#include "NOTA.H"




float leer_frecuencia_tramo(note_t *nota){ //transfoma la nota del note_t en su numero posicional(nota_t). 
	int i;

	for(i = 0; i < 12; i++)
		if(! strcmp(nota->nota, notas[i]))
			break;

	return 440 * (pow((1.0) / 2, 4 - nota->octava)) * (pow(2, (i - 9) / 12));
}

double calcular_tf(note_t *nota, float td){  //genera el tiempo final para usar en tramo_muestreo.
	return nota->t0 + nota->duracion + td;
}

float **generar_matriz_armonicos(synt_t synt){      // carga los datos recibidos de los vectores multiplicador,intensidad en una matriz.

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


void destruir_matriz(float **r, size_t cantidad_de_columnas){ //si bien siempre vamos a tener dos columnas en la matriz por las dudas puse la cantidad de columnas.
	for(size_t i = 0; i < cantidad_de_columnas; i++)
		free(r[i]);
	
	free(r);
}


//HAY QUE CREAR TRADUCCION DE FUNCIONES DE MODULACION.


//prototipo para funcion m(t) de modulacion (usamos la relacion que hay entre (i en el for) y el tiempo puede ser que no este bien el n_de_sostenido 

tramo_t *modulacion(tramo_t *t, synt_t *synt){
    size_t n_ataque = t->f_m * (synt->parametros[0][0] - t->t0)      //aca estas calulando hasta que n se aplica la funcion de ataque 
    size_t n_sostenido = t->f_m * (synt->parametros[0][1] - synt->parametros[0][0]) //calculas hasta que n se aplica el sostenido

    funcion_t func[3];

    for(size_t i = 0; i < t->n; i++){
		if(i < n_ataque)
    		t->v[i] = t->v[i] * codificar_funcion(func[0]);//(la funcion correspondiente de modulacion de ataque );

	    else if(i < n_sostenido)
	        t->v[i] = t->v[i] * codificar_funcion(func[1]);//(la funcion correspondiente de modulacion);

        t->v[i] = t->v[i] * codificar_funcion(func[2]);//(la funcion de decaimiento);
   }

   return t;
}


tramo_t *sintetizar_cancion(note_t v[],size_t tamagno,synt_t * w ,int fre_mtro){
	float ** t=genera_matriz(synt_t->frecuencia,syn_t->intensidad,sint_t->cantidad_armonicos);
	for(size_t i=0;i<tamagno;i++){
		float p=_leer_frecuencia(v[i]->octava,v[i]->nota);
		double tf=_calcula_tf(v[i]->t0,v[i]->duracion,w->parametros[0][3]);//params [0][3] <- creo que esa es la posicion donde se encuntra tiempo de decaimiento
		tramo_t * muestrea_nota=tramo_crear_muestreo(v[i]->t0,tf,fre_mtro,p,v[i]->intensidad,t,w->cantidad_armonicos);
		/*aca iria la funcion que modulariza el tramo_t no estaria viendo como aplicarla , mi idea es hacer un puntero a funciones ya que la funcion de modularizacion 
		 * tiene que usar las funciones que definimos en funciones_modulacion.c . la implementacion (creo) seria recorrer el tramito generado y comparando el tiempo 
		 * por lo tanto habbria que hacer algo asi (lee el prototipo de la funcion );
		 


		//despues de lo anterior hay que pasarle el tramo modularizado a tramo_extender 
		*/
	}
	destruir_matriz(t);
	return el tramo con todas las notas sumadas!;
}

// me quedo por pensar como escalar el tramo para pasarselo al wave , espero que se entienda todo lo anterior 



