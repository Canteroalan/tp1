#ifndef NOTA_H
#define NOTA_H


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct {
    char nombre[30];
    short int longitud;
    uint8_t valor;
} _evento_t;

typedef enum {
    PISTA_UNICA,
    MULTIPISTAS_SINCRONICAS,
    MULTIPISTAS_ASINCRONICAS,
} formato_t ;

typedef enum {
    NOTA_APAGADA,
    NOTA_ENCENDIDA,
    NOTA_DURANTE,
    CAMBIO_DE_CONTROL,
    CAMBIO_DE_PROGRAMA,
    VARIAR_CANAL,
    CAMBIO_DE_PITCH,
    METAEVENTO
}evento_t;

typedef enum {
        DO,
        DO_BEMOL,
        RE,
        RE_BEMOL,
        MI,
        FA,
        FA_BEMOL,
        SOL,
        SOL_BEMOL,
        LA,
        LA_BEMOL,
        SI,
} nota_t ;


//TDA de una nota.
typedef struct _note {
    float  intensidad; //Tono de la nota.
    double t0; //Tiempo de inicio de la nota.
    double duracion; //Tiempo de duracion de la nota.
    unsigned char octava; //Octava de la nota.
    const char *nota; //Nombre de la nota.
}note_t;

//TDA de un contenedor de notas.
typedef struct _contenedor{
    size_t cant_notas; //Cantidad de notas dentro del contenedor.
    note_t *notes; //Vector de notas dentro del contenedor.
}nota_contenedor_t;


//ej4
bool decodificar_formato(uint16_t valor, formato_t *formato);
bool decodificar_evento(uint8_t valor, evento_t *evento, char *canal, int *longitud);
bool decodificar_nota(uint8_t valor, nota_t *nota, signed char *octava);
const char *codificar_formato(formato_t formato);
const char *codificar_evento(evento_t evento);
const char *codificar_nota(nota_t nota);

//ej5
uint8_t leer_uint8_t(FILE *f);
uint16_t leer_uint16_big_endian(FILE *f);
uint32_t leer_uint32_big_endian(FILE *f);
bool leer_encabezado(FILE *f, formato_t *formato, uint16_t *numero_pistas, uint16_t *pulsos_negra);
bool leer_pista(FILE *f, uint32_t *tamagno);
bool leer_tiempo(FILE *f, double *tiempo, int pps);
bool leer_evento(FILE *f, evento_t *evento, char *canal, int *longitud, uint8_t mensaje[]);
void descartar_metaevento(FILE *f, uint8_t tamagno);


//nota.c
note_t *crear_note_t(void);
nota_contenedor_t *crear_nota_contenedor_t(FILE *f, char canal, int pps);
void destruir_note_t(note_t *note);
void destruir_nota_contenedor_t(nota_contenedor_t *t);
bool leer_notas(FILE *f, nota_contenedor_t *contenedor,char channel, int pps);
float leer_frecuencia_nota(note_t nota);


#endif
