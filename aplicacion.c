#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdint.h>
#include<string.h>

#include"tramo.h"



float _leer_frecuencia(signed char octava,const char* nota){ //transfoma la nota del note_t en su numero  posicional(nota_t). 
	int i;
	for(i=0;i<12;i++){
		if(!strcmp(nota,notas[i]))
			break;
	}
	return 440*(pow((1.0)/2,4-octava))*(pow(2,(i-9)/12));
}

double _calcula_tf(double t0,uint32_t duracion,float td){  //genera el tiempo final para usar en tramo_muestreo.
	return t0+duracion+td;
}

float ** genera_matriz(float *a,float *b,size_t n){      // carga los datos recibidos de los vectores multiplicador,intensidad en una matriz.
	float ** armonicos=malloc(2*sizeof(float*));

	if(armonicos == NULL)
		return NULL;

	for(int i=0;i<2;i++){
		float * almacenador=malloc(n*sizeof(float));

		if(almacenador == NULL){
			free(armonicos);
			return NULL;
		}
		armonicos[i]=almacenador;
	}
	for(size_t j=0;j<n;j++){
		armonicos [j][0]=a[j];
		armonicos [j][1]=b[j];
	}
	return armonicos;
}
//prototipo para funcion m(t) de modularizacion ( usamos la relacion que hay entre (i en el for) y el tiempo puede ser que no este bien el n_de_sostenido 

tramo_t* modularizacion(tramo_t * t){
           size_t n_de_ataque=t->f_m*(tiempo de ataque - t->t0)      //aca estas calulando hasta que n se aplica la funcion de ataque 
	   size_t n_de_sostenido=t->f_m(tiempo de sostenido-tiempo de ataque) //calculas hasta que n se aplica el sostenido
	   for(size_t i=0;i<t->n;i++){
	          if(i<n_de_ataque)
		          t->v[i]=t->v[i]* //(la funcion correspondiente de modulacion de ataque );
	          if(i>n_de_ataque && i<n_de_sostenido)
		         t->v[i]=t->v[i]*  //(la funcion correspondiente de modulacion);
	          if(i>n_de_sostenido)
		         t-> v[i]=t->v[i]*  //(la funcion de decaimiento);
	   }
	   return t;
}


void destruir_matriz(float ** r,int cantidad_de_columnas){ //si bien siempre vamoos a tener dos columnas en la matriz por las dudas puse la cantidad de columnas.
	for(size_t i=0;i<cantidad_de_columnas;i++)
		free(r[i]);
	free(r);
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


	       	




