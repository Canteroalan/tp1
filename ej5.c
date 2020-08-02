#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>

#include"ej4.h"
#include"ej5.h"

#define NRO_MAGICO_ENCABEZADO 0x4D546864
#define NRO_MAGICO_PISTA      0x4D54726B
#define MASK_TIEMPO           0x80
#define MASK_ALMACENA_BITS    0X7F
#define SHIFT_TIEMPO          7

uint8_t leer_uint8_t(FILE *f){
        uint8_t elemento8;
        fread(&elemento8,sizeof(char),1,f);
        return elemento8;
}

uint16_t leer_uint16_big_endian(FILE *f){
	uint16_t elemento16;
        uint8_t vector[2];
        for(int i=0;i<2;i++)
                vector[i]=leer_uint8_t(f);
        return elemento16=((vector[0]<<8) | vector[1]);
}

uint32_t leer_uint32_big_endian(FILE *f){
        uint32_t elemento32;
        uint16_t vector[2];
        for(int i=0;i<2;i++)
                vector[i]=leer_uint16_big_endian(f);
        return elemento32=((vector[0]<<16) | vector[1]);
}

bool leer_encabezado(FILE *f, formato_t *formato, uint16_t *numero_pistas, uint16_t *pulsos_negra){
        if(leer_uint32_big_endian(f) != NRO_MAGICO_ENCABEZADO)
                return false;
        if(leer_uint32_big_endian(f) != 6)
                return false;
        if(!decodificar_formato(leer_uint16_big_endian(f),formato))
	        return false;
        *numero_pistas=leer_uint16_big_endian(f);
        *pulsos_negra=leer_uint16_big_endian(f);
        return true;
}

bool leer_pista(FILE *f, uint32_t *tamagno){
	if(leer_uint32_big_endian(f) != NRO_MAGICO_PISTA)
		return false;
	*tamagno=leer_uint32_big_endian(f);
	return true;
}

bool leer_tiempo(FILE *f, uint32_t *tiempo){
        uint8_t vector[4];
        size_t i;
	*tiempo=0;
        for(i=0;((vector[i]=leer_uint8_t(f)) & MASK_TIEMPO);i++){
                if(i>3)
                        return false;
	}
        for(size_t j=0;j<=i;j++)
                *tiempo|=(vector[j] & MASK_ALMACENA_BITS) <<(SHIFT_TIEMPO*(i-j));
        return true;
}


bool leer_evento(FILE *f, evento_t *evento, char *canal, int *longitud, uint8_t mensaje[]){
        uint8_t valor= leer_uint8_t(f);
        if(decodificar_evento(valor,evento,canal,longitud)){
		for(size_t i=0;i<(*longitud);i++){
                        mensaje[i]=leer_uint8_t(f);
		}
		return true;
        }
	mensaje[0]=valor;
        for(size_t i=1;i<(*longitud);i++){
                mensaje[i]=leer_uint8_t(f);
	}
	return true;
}

void descartar_metaevento(FILE *f, uint8_t tamagno){
	for(size_t i=0;i<tamagno;i++)
		leer_uint8_t(f);
}
        



                                          
