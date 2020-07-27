#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>



typedef void (*valor_t)();

typedef struct {
	char *parametro;
	void (*valor)();
}parametro_t;

static const parametro_t parametros[] = {
    {"-s", synth},
    {"-i", midi},
    {"-o", wave},
    {"-c", canal},
    {"-f", frec},
    {"-r", pulsos}
};

void uso(char *argv[]) {
    fprintf(stderr, "El programa recive una entrada.mid, un sintetizador.txt y parametros opcionales que generan un arvhibo.wav.\n");
    fprintf(stderr, "Uso\n\t%s -s <sintetizador.txt> -i <entrada.mid> -o <salida.wav> [-c <canal>] [-f <frecuencia>] [-r <pulsosporsegundo>]\n", argv[0]);
}



FILE *synth(){

}

FILE *midi(){

}

FILE *wave(){

}

size_t canal(){

}

int frec(){

}

??? pulsos(){
	
}




