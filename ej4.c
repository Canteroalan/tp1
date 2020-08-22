#include<stdint.h>
#include<stdbool.h>

#include "NOTA.H"

#define MASK_FORMATO 0xfffc
#define MASK_CANAL  0x0f
#define MASK_NOTA   0x80

const char *formatos[] = {
        [PISTA_UNICA] = "pista unica",
        [MULTIPISTAS_SINCRONICAS] = "multipista sincronica",
        [MULTIPISTAS_ASINCRONICAS] = "multipista asincronica",
};

const _evento_t eventos[] = {
        [NOTA_APAGADA] = {"nota apagada", 2},
        [NOTA_ENCENDIDA] = {"nota encendida", 2},
        [NOTA_DURANTE] = {"nota durante", 2},
        [CAMBIO_DE_CONTROL] = {"cambio de control", 2},
        [CAMBIO_DE_PROGRAMA] = {"cambio de programa", 1},
        [VARIAR_CANAL] = {"variar canal", 1},
        [CAMBIO_DE_PITCH] = {"cambio de pitch", 2},
        [METAEVENTO] = {"metaevento", 2}
};

const char *notas[] = {
        [DO] = "C",
        [DO_BEMOL] = "C#",
        [RE] = "D",
        [RE_BEMOL] = "D#",
        [MI] = "E",
        [FA] = "F",
        [FA_BEMOL] = "F#",
        [SOL] = "G",
        [SOL_BEMOL] = "G#",
        [LA] = "A",
        [LA_BEMOL] = "A#",
        [SI] = "B"
};

bool decodificar_formato(uint16_t valor, formato_t *formato){
        if(valor & MASK_FORMATO)
                return false;
        
        *formato = valor;
                
        return true;
}

bool decodificar_evento(uint8_t valor, evento_t *evento, char *canal, int *longitud){
        if((valor & MASK_NOTA) == 0)
                return false;

        *evento = (valor  & ~MASK_NOTA) >> 4;
        *canal = valor & MASK_CANAL;
        *longitud = eventos[*evento].longitud;
        
        return true;
}

bool decodificar_nota(uint8_t valor, nota_t *nota, signed char *octava){
        if(valor & MASK_NOTA){
                return false;
        }

        *nota = (valor % 12);
        *octava = (valor / 12) - 1;
        
        return true;
}

const char *codificar_formato(formato_t formato){
        return formatos[formato];
}

const char *codificar_evento(evento_t evento){
        return eventos[evento].nombre;
}

const char *codificar_nota(nota_t nota){
        return notas[nota];
}

