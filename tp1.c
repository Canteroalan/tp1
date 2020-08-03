#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>


#include "ARGUMENTOS.H"
#include "NOTA.H"

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
	int frec = leer_frecuencia(argc, argv);
	int pulso = leer_pulso(argc, argv);

	
	note_t *note = leer_notas(m);
	if(note == NULL){
		fclose(s);
		fclose(m);
		fclose(w);
		return 1;
	}


	fclose(s);
	fclose(m);
	fclose(w);

	return 0;
}


