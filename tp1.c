#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>


#include "ARGUMENTOS.H"
#include "SINTETIZADOR.H"
#include "TRAMO.H"

//$ ./sintetizador -s <sintetizador.txt> -i <entrada.mid> -o <salida.wav> [-c <canal>] [-f <frecuencia>] [-r <pulsosporsegundo>]


int main(int argc, char *argv[]){
	if(argc < 7){
		uso(argv);
		return 1;
	}

	FILE *s = abrir_sintetizador(argc, argv);
	if(s == NULL){
		uso(argv);
		return 1;
	}

	FILE *m = abrir_midi(argc, argv);
	if(m == NULL){
		uso(argv);
		fclose(s);
		return 1;
	}

	FILE *w = abrir_wave(argc, argv);
	if(w == NULL){
		uso(argv);
		fclose(s);
		fclose(m);
		return 1;
	}

	char canal = leer_canal(argc, argv);
	int f_m = leer_frecuencia(argc, argv);
	int pps = leer_pulso(argc, argv);



	


	synt_t *synt = crear_synt_t(s);
	if(synt == NULL){
		destruir_nota_contenedor_t(contenedor);
		fclose(s);
		fclose(m);
		fclose(w);
		return 1;
	}


	//imprimir_synt_t(synt);




	if(! escribir_wave(w, n, f_m, int16_t *v)){
		destruir_nota_contenedor_t(contenedor);
		destruir_synt_t(synt);
		fclose(s);
		fclose(m);
		fclose(w);
		return 1;
	}




	destruir_nota_contenedor_t(contenedor);
	destruir_synt_t(synt);
	fclose(s);
	fclose(m);
	fclose(w);

	return 0;
}


