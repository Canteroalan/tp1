#ifndef EJ4_H
#define EJ4_H

#include<stdint.h>
#include<stdbool.h>

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
        METAEVENTO,
} evento_t;

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

bool decodificar_formato(uint16_t valor, formato_t *formato);

bool decodificar_evento(uint8_t valor,evento_t *evento,char *canal,int *longitud);

bool decodificar_nota(uint8_t valor,nota_t *nota,signed char *octava);

const char *codificar_formato(formato_t formato);

const char *codificar_evento(evento_t evento);

const char *codificar_nota(nota_t nota);

#endif // EJ4_H
