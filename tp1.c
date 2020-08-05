#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>


#include "ARGUMENTOS.H"
#include "NOTA.H"
#include "SINTETIZADOR.H"

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
	int pps = leer_pulso(argc, argv);

	
	note_t *note = crear_note_t();
	if(note == NULL){
		fclose(s);
		fclose(m);
		fclose(w);
		return 1;
	}

	size_t cant_notas;

	if(! leer_notas(s, note, &cant_notas, pps)){
		destruir_note_t(note);
		fclose(s);
		fclose(m);
		fclose(w);
		return 1;
	}
	//Se imprime por pantalla note dentro de leer_notas en nota.c.


	synt_t *synt = crear_synt_t(s);
	if(synt == NULL){
		fclose(s);
		return 1;
	}

	if(! leer_sintetizador(s, synt)){
		destruir_synt_t(synt);
		destruir_note_t(note);
		fclose(s);
		fclose(m);
		fclose(w);
		return 1;
	}

	imprimir_synt_t(synt);


	// Se tiene que generar el muestreo del tramo f(t):
	// Frecuencia e intensidad de cada nota, armonicos de la matriz generada con generar_matriz_armonicos.

	// Luego se lo multiplica por las funciones de modulacion en los distintos tiempos m(t):
	// Llamar a una funcion modulacion() que reciba como parametros las 3 funciones de modulacion y sus parametros.

	// Para finalizar muliplicar f(t) con m(t) en sus intervalos correspondientes.



	destruir_note_t(note);
	destruir_synt_t(synt);
	fclose(s);
	fclose(m);
	fclose(w);

	return 0;
}


