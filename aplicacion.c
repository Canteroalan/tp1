#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdint.h>
#include<string.h>

#include"TRAMO.H"



float leer_frecuencia_tramo(signed char octava, const char *nota){ //transfoma la nota del note_t en su numero posicional(nota_t). 
	int i;

	for(i = 0; i < 12; i++)
		if(! strcmp(nota, notas[i]))
			break;

	return 440 * (pow((1.0) / 2, 4 - octava)) * (pow(2, (i - 9) / 12));
}

double calcular_tf(double t0, uint32_t duracion, float td){  //genera el tiempo final para usar en tramo_muestreo.
	return t0 + duracion + td;
}

float **generar_matriz_armonicos(float *frecuencia, float *intensidad, size_t cant_armonicos){      // carga los datos recibidos de los vectores multiplicador,intensidad en una matriz.

	float **armonicos = malloc(2 * sizeof(float *));
	if(armonicos == NULL)
		return NULL;

	for(size_t i = 0; i < 2; i++){

		float *almacenador = malloc(cantidad_armonicos * sizeof(float));
		if(almacenador == NULL){
			free(armonicos);
			return NULL;
		}

		armonicos[i] = almacenador;
	}

	for(size_t j = 0; j < cant_armonicos; j++){
		armonicos [j][0] = frecuencia[j];
		armonicos [j][1] = intensidad[j];
	}

	return armonicos;
}

// Creo que se puede hacer sin usar memoria dinamica ya que tenemos la cant_armonicos.
// f[] son las frecuencias, a[] las intensidades leidas por sintetizador.txt. 
// Creo que esta bien lo que hizo Alan ya que no podria devolver el vector. PREGUNTAR ALAN


void destruir_matriz(float **r, size_t cantidad_de_columnas){ //si bien siempre vamoos a tener dos columnas en la matriz por las dudas puse la cantidad de columnas.
	for(size_t i = 0; i < cantidad_de_columnas; i++)
		free(r[i]);
	
	free(r);
}




//prototipo para funcion m(t) de modulacion ( usamos la relacion que hay entre (i en el for) y el tiempo puede ser que no este bien el n_de_sostenido 

tramo_t *modulacion(tramo_t *t){
    size_t n_de_ataque = t->f_m * (tiempo de ataque - t->t0)      //aca estas calulando hasta que n se aplica la funcion de ataque 
    size_t n_de_sostenido = t->f_m * (tiempo de sostenido - tiempo de ataque) //calculas hasta que n se aplica el sostenido

    for(size_t i = 0; i < t->n; i++){
		if(i < n_de_ataque)
    		t->v[i] = t->v[i] * //(la funcion correspondiente de modulacion de ataque );

	    if(i > n_de_ataque && i < n_de_sostenido)
	        t->v[i] = t->v[i] *  //(la funcion correspondiente de modulacion);

        if(i > n_de_sostenido)
	        t->v[i] = t->v[i] *  //(la funcion de decaimiento);
   }

   return t;
}


tramo_t * sintetiza_cancion(note_t v[],size_t tamagno,synt_t * w ,int fre_mtro){
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



