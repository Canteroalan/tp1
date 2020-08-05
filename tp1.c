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

	crear_nota_t *contenedor = crear_nota_contenedro_t(cant_notas, note);
	if(contenedor == NULL){
		destruir_note_t(note);
		fclose(s);
		fclose(m);
		fclose(w);
		return 1;
	}


	synt_t *synt = crear_synt_t(s);
	if(synt == NULL){
		destruir_nota_contenedor_t(contenedor);
		destruir_synt_t(synt);
		destruir_note_t(note);
		fclose(s);
		fclose(m);
		fclose(w);
		return 1;
	}

	if(! leer_sintetizador(s, synt)){
		destruir_nota_contenedor_t(contenedor);
		destruir_synt_t(synt);
		destruir_note_t(note);
		fclose(s);
		fclose(m);
		fclose(w);
		return 1;
	}

	//imprimir_synt_t(synt);



	destruir_nota_contenedor_t(contenedor);
	destruir_note_t(note);
	destruir_synt_t(synt);
	fclose(s);
	fclose(m);
	fclose(w);

	return 0;
}


