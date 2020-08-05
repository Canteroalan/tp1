#ifndef NOTA
#define NOTA

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


typedef enum {
        PISTA_UNICA,
        MULTIPISTAS_SINCRONICAS,
        MULTIPISTAS_ASINCRONICAS
}formato_t;

typedef enum {
        NOTA_APAGADA,
        NOTA_ENCENDIDA,
        NOTA_DURANTE,
        CAMBIO_CONTROL,
        CAMBIO_PROGORAMA,
        VARIAR_CANAL,
        CABIO_PITCH,
        METAEVENTO
}evento_t;

typedef enum { DO, REb, RE, MIb, MI, FA, SOLb, SOL, LAb, LA, SIb, SI }nota_t;



typedef struct {
        float  intensidad;
        double t0;
        uint32_t duracion;
        unsigned char octava;
        const char *nota;
} note_t ;



bool decodificar_formato(uint16_t valor, formato_t *formato);
bool decodificar_evento(uint8_t valor, evento_t *evento, char *canal, int *longitud);
bool decodificar_nota(uint8_t valor, nota_t *nota, signed char *octava);

const char *codificar_formato(formato_t formato);
const char *codificar_evento(evento_t evento);
const char *codificar_nota(nota_t nota);



uint8_t leer_uint8_t(FILE *f);
uint16_t leer_uint16_big_endian(FILE *f);
uint32_t leer_uint32_big_endian(FILE *f);
bool leer_encabezado(FILE *f, formato_t *formato, uint16_t *numero_pistas, uint16_t *pulsos_negra);
bool leer_pista(FILE *f, uint32_t *tamagno);
bool leer_tiempo(FILE *f, double *tiempo, int pps);
bool leer_evento(FILE *f, evento_t *evento, char *canal, int *longitud, uint8_t mensaje[]);
void descartar_metaevento(FILE *f, uint8_t tamagno);



note_t *crear_note_t(void);
bool leer_notas(FILE *f, note_t *note, size_t *cant_notas, int pps);
void destruir_note_t(note_t *note);

#endif
