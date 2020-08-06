#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


#include "NOTA.H"


#define MASK_FORMATO 0XFFFC
#define MASK_E3 0x80
#define MASK_EVENTO 0X70
#define SHIFT_EVENTO 4
#define MASK_CANAL 0x0F
#define MASK_NOTA 0x80
#define SHIFT_NOTA 7


struct traduccion_formato {
	char *cadena;
};

static const struct traduccion_formato formatos[] = {
	{"pista unica"},
	{"multipista sincronica"},
	{"multipista asincronica"}
};


struct traduccion_evento {
	int longitud;
	char *cadena;
};

static const struct traduccion_evento eventos[] = {
	{2, "nota apagada"},
	{2, "nota encendida"},
	{2, "nota durante"},
	{2, "cambio de control"},
	{1, "cambio de programa"},
	{1, "variar canal"},
	{2, "cambio de pitch"},
	{2, "metaevento"}
};

static const char *notas[] = {
	[DO] = "C", 
	[REb] = "C#", 
	[RE] = "D", 
	[MIb] = "D#", 
	[MI] = "E", 
	[FA] = "F", 
	[SOLb] = "F#", 
	[SOL] = "G", 
	[LAb] = "G#", 
	[LA] = "A", 
	[SIb] = "A#", 
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

        *evento = (valor  & (~MASK_NOTA)) >> SHIFT_EVENTO;

        *canal = valor & MASK_CANAL;

        *longitud = eventos[*evento].longitud;
        
        return true;
}

bool decodificar_nota(uint8_t valor, nota_t *nota, signed char *octava){
	if((valor & MASK_NOTA))
		return false;

	*nota = valor % 12;
	*octava = (valor / 12) - 1;

	return true;
}


const char *codificar_formato(formato_t formato){
	return formatos[formato].cadena;
}

const char *codificar_evento(evento_t evento){
	return eventos[evento].cadena;
}

const char *codificar_nota(nota_t nota){
	return notas[nota];
}