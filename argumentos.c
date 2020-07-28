#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#include "ARGUMENTOS.h"


void uso(char *argv[]) {
    fprintf(stderr, "El programa recive una entrada.mid, un sintetizador.txt y parametros opcionales que generan un arvhibo.wav.\n");
    fprintf(stderr, "Uso\n\t%s -s <sintetizador.txt> -i <entrada.mid> -o <salida.wav> [-c <canal>] [-f <frecuencia>] [-r <pulsosporsegundo>]\n", argv[0]);
}

FILE *abrir_sintetizador(int argc, char *argv[]){
    for(size_t i = 0; i < argc; i++){
        
        if(! strcmp(argv[i], "-s")){
            
            FILE *s = fopen(argv[i + 1], "rt");
            if(s == NULL)
                return NULL;
            
            return s;
        }
    }

    fprintf(stderr, "No habia ningun sintetizador.txt para abrir\n");
    return NULL;
}

FILE *abrir_midi(int argc, char *argv[]){
    for(size_t i = 0; i < argc; i++){
        
        if(! strcmp(argv[i], "-i")){
            
            FILE *m = fopen(argv[i + 1], "rb");
            if(m == NULL)
                return NULL;
            
            return m;
        }
    }

    fprintf(stderr, "No habia ningun archivo.mid para abrir\n");
    return NULL;
}

FILE *abrir_wave(int argc, char *argv[]){
    for(size_t i = 0; i < argc; i++){
        
        if(! strcmp(argv[i], "-o")){
            
            FILE *w = fopen(argv[i + 1], "wb");
            if(w == NULL)
                return NULL;
            
            return w;
        }
    }

    fprintf(stderr, "No habia ningun archivo.wav para abrir\n");
    return NULL;
}

char leer_canal(int argc, char *argv[]){
    char canal;
    size_t i;

    for(i = 0; i < argc; i++){
        if(! strcmp(argv[i], "-c")){
            &canal = argv[i + 1];
            break;
        }
    }

    if(i == argc)
        canal = '0';

    return canal;
}

int leer_frecuencia(int argc, char *argv[]){
    int frec;
    size_t i;

    for(i = 0; i < argc; i++){
        if(! strcmp(argv[i], "-f")){
            frec = atoi(argv[i + 1]);
            break;
        }
    }

    if(i == argc)
        frec = 44100;

    return frec;
}

int leer_pulso(int argc, char *argv[]){
    int pulso;
    size_t i;

    for(i = 0; i < argc; i++){
        if(! strcmp(argv[i], "-r")){
            pulso = atoi(argv[i + 1]);
            break;
        }
    }

    /*if(i == argc)
        pulsoso = ???;*/

    return pulso;
}








