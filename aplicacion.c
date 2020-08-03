#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdint.h>

#include"tramo.h"



float leer_frecuencia(signed char octava,nota_t nota){ // aca hay que tratar de convertir el char * nota a un nota_t que definimos en el ej4
	return 440*(pow((1.0)/2,4-octava))*(pow(2,(nota-9)/12));
}

double calcula_tf(uint32_t t0,uint32_t duracion,float td){
	return t0+duracion+td;
}

tramo_t * sintetiza_cancion(note_t v[],size_t tamagno,synt_t * w ){
	for(size_t i=0;i<tamagno;i++){
		float frecuencia=leer_frecuencia(v[i]->octava,/*aca iria el nota_t*/);
		double tf=calcula_tf(v[i]->t0,v[i]->duracion,w->parametros[0][3]);// creo que esa es la posicion donde se encuntra td 




