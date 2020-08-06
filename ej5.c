#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "NOTA.H"

#define SHIFT_8 8 
#define SHIFT_16 16 
#define MTHD 0x4D546864
#define MTRK 0x4D54726B
#define MASK_TIEMPO 0x7F
#define SHIFT_TIEMPO 7
#define MASK_E3 0x80


uint8_t leer_uint8_t(FILE *f){
	uint8_t v;

	fread(&v, sizeof(uint8_t), 1, f);
	
	return v;
}

uint16_t leer_uint16_big_endian(FILE *f){
	uint8_t v[2];
	uint16_t t;
	
	for(size_t i = 0; i < 2; i++)
		v[i] = leer_uint8_t(f);

	t = (v[0] << SHIFT_8) | v[1];

	return t;
}

uint32_t leer_uint32_big_endian(FILE *f){
	uint16_t v[2];
	uint32_t t;

	for(size_t i = 0; i < 2; i++)
		v[i] = leer_uint16_big_endian(f);

	t = (v[0] << SHIFT_16) | v[1];

	return t;
}


bool leer_encabezado(FILE *f, formato_t *formato, uint16_t *numero_pistas, uint16_t *pulsos_negra){

	uint32_t t[2];
	uint16_t v[3];
	size_t i = 0;

	for(;i < 2; i++)
		t[i] = leer_uint32_big_endian(f);

	if(t[0] != MTHD || t[1] != 6)
		return false;

	for(i = 0; i < 3; i++)
		v[i] = leer_uint16_big_endian(f);

	if((decodificar_formato(v[0], formato)) == false)
		return false;

	*numero_pistas = v[1];
	*pulsos_negra = v[2];

	return true;
}

bool leer_pista(FILE *f, uint32_t *tamagno){
	uint32_t id;

	id = leer_uint32_big_endian(f);
	
	if(id != MTRK)
		return false;

	*tamagno = leer_uint32_big_endian(f);

	return true;
}

bool leer_tiempo(FILE *f, double *tiempo, int pps){
	uint8_t t[4];
	size_t i = 0;
	uint32_t time = 0;

	while(((t[i] = leer_uint8_t(f)) & MASK_E3) == MASK_E3)
		i++;

	if (i > 3)
		return false;
	

	for(size_t n = 0; n <= i; n++){
		time |= ((t[n] & MASK_TIEMPO) << (SHIFT_TIEMPO * (i - n)));
	}

	*tiempo =(double) time / pps;

	return true;
}

bool leer_evento(FILE *f, evento_t *evento, char *canal, int *longitud, uint8_t mensaje[]){
    uint8_t valor = leer_uint8_t(f);
    
    if(decodificar_evento(valor, evento, canal, longitud)){
		
		for(size_t i = 0; i < (*longitud); i++){
            mensaje[i] = leer_uint8_t(f);
		}

		return true;
    }

	mensaje[0] = valor;

    for(size_t i = 1; i < (*longitud); i++){
        mensaje[i] = leer_uint8_t(f);
    }

	return true;
}

void descartar_metaevento(FILE *f, uint8_t tamagno){

	for(size_t i = 0; i < tamagno; i++)
		leer_uint8_t(f);
}