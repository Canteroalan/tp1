
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>




bool leer_sintetizador(FILE *s){
	uint8_t n;
	char *q = NULL;
	
	n = atoi(fgets(q, sizeof(int), s));

	for(size_t i = 0; i < n; i++)
		printf("%x\n", n);

	//En vez de leer 8 lee un 56 (que es el codigo ASCII del 8)
	//Pero no nos sirve porque necesitamos que lea 8,
	//Por el ejemplo delarchivo de sintetizador del enunciado.


	//Aca leeria las cantidad de frecuencias(f) e intensidades(a) que
	//leimos en el primer fread.


	//Y aca leeria las 3 funciones (ataque, sostenido, decaimiento).
	//Aca se implementa lo de los punteros a funciones.
	
	return true;
}


int main(int argc, char *argv[]){
	
	FILE *s = fopen(argv[1], "rt");
	if(s == NULL){
		fclose(s);
		return 1;
	}

	if(! leer_sintetizador(s)){
		fclose(s);
		return 1;
	}

	fclose(s);

	return 0;
}

