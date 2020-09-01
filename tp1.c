#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>


#include "ARGUMENTOS.H"
#include "TRAMO.H"

//$ ./sintetizador -s <sintetizador.txt> -i <entrada.mid> -o <salida.wav> [-c <canal>] [-f <frecuencia>] [-r <pulsosporsegundo>]


int main(int argc, char *argv[]){
	
	FILE *s;
	FILE *m;
	FILE *w;
	char canal;
	int f_m;
	int pps;

	if(! procesar_argumentos(argc, argv, &s, &m, &w, &canal, &f_m, &pps))
		return 1;

	size_t n;

	int16_t *v = sintetizar_cancion(m, s, f_m, &n, canal, pps);
	if(v == NULL){
		fclose(s);
		fclose(m);
		fclose(w);
		return 1;
	}

	escribir_wave(w, n, f_m, v);
	
	destruir_int16_t(v);
	fclose(s);
	fclose(m);
	fclose(w);

	return 0;
}


