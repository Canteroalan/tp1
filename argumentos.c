#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#include "ARGUMENTOS.H"


void uso(char *argv[]) {
    fprintf(stderr, "El programa recive una entrada.mid, un sintetizador.txt y parametros opcionales que generan un arvhibo.wav.\n");
    fprintf(stderr, "Uso\n\t%s -s <sintetizador.txt> -i <entrada.mid> -o <salida.wav> [-c <canal>] [-f <frecuencia>] [-r <pulsosporsegundo>]\n", argv[0]);
}

FILE *abrir_sintetizador(int argc, char *argv[]){
    for(size_t i = 1; i < argc; i++){
        
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
    for(size_t i = 1; i < argc; i++){
        
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
    for(size_t i = 1; i < argc; i++){
        
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
    uint8_t canal;
    size_t i;

    for(i = 1; i < argc; i++){
        if(! strcmp(argv[i], "-c")){
            canal = atoi(argv[i + 1]);
            break;
        }
    }

    if(i == argc)
        canal = 0;

    return canal;
}

int leer_frecuencia(int argc, char *argv[]){
    int frec;
    size_t i;

    for(i = 1; i < argc; i++){
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

    for(i = 1; i < argc; i++){
        if(! strcmp(argv[i], "-r")){
            pulso = atoi(argv[i + 1]);
            break;
        }
    }

    /*if(i == argc)
        pulsoso = ???;*/

    return pulso;
}


bool escribir_wave(FILE *w, size_t n, int f_m, int16_t *v){
    char chunk_id[4] = "RIFF";
    uint32_t chunk_size = 36 + 2 * n; //falta n.
    char format[4] = "WAVE";
    char sub_chunk1_id[4] = "fmt ";
    uint32_t sub_chunk1_size = 16;
    uint16_t audio_format = 1;
    uint16_t num_channels = 1;
    uint32_t sample_rate = f_m; //frecuencia que leemos de argumentos.
    uint32_t byte_rate = 2 * sample_rate;
    uint16_t block_align = 2;
    uint16_t bits_per_sample = 16;
    char sub_chunk2_id[4] = "data";
    uint32_t sub_chunk2_size = 2 * n;
    int16_t data[n]; //me la dan en los parametros. Secuencia de n muestras.



    if(fwrite(chunk_id, sizeof(char), 4, w) != 4)
        return false;

    if(fwrite(&chunk_size, sizeof(uint32_t), 1, w) != 1)
        return false;

    if(fwrite(format, sizeof(char), 4, w) != 4)
        return false;

    if(fwrite(sub_chunk1_id, sizeof(char), 4, w) != 4)
        return false;

    if(fwrite(&sub_chunk1_size, sizeof(uint32_t), 1, w) != 1)
        return false;

    if(fwrite(&audio_format, sizeof(uint16_t), 1, w) != 1)
        return false;

    if(fwrite(&num_channels, sizeof(uint16_t), 1, w) != 1)
        return false;

    if(fwrite(&sample_rate, sizeof(uint32_t), 1, w) != 1)
        return false;

    if(fwrite(&byte_rate, sizeof(uint32_t), 1, w) != 1)
        return false;

    if(fwrite(&block_align, sizeof(uint16_t), 1, w) != 1)
        return false;

    if(fwrite(&bits_per_sample, sizeof(uint16_t), 1, w) != 1)
        return false;

    if(fwrite(sub_chunk2_id, sizeof(char), 4, w) != 4)
        return false;

    if(fwrite(&sub_chunk2_size, sizeof(uint32_t), 1, w) != 1)
        return false;

    if(fwrite(data, sizeof(int16_t), n, w) != n)
        return false;
    
    return true;
}





