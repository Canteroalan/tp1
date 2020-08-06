#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>


#include "NOTA.H"


#define METAEVENTO_FIN_DE_PISTA 0x2F
#define EVENTO_MAX_LONG 10


enum {EVNOTA_NOTA, EVNOTA_VELOCIDAD};
enum {METAEVENTO_TIPO, METAEVENTO_LONGITUD};



note_t *crear_note_t(void){
    note_t *note = malloc(sizeof(note_t) * 20); //Primeras 20 notas.
    if(note == NULL){
        fprintf(stderr, "Fallo malloc note\n");
        return NULL;
    }

    return note;
}

nota_contenedor_t *crear_nota_contenedor_t(FILE *f, char canal, int pps){
    nota_contenedor_t *contenedor = malloc(sizeof(nota_contenedor_t));
    if(contenedor == NULL)
        return NULL;

    contenedor->notes = crear_note_t();
    if(contenedor->notes == NULL){
        free(contenedor);
        return NULL;
    }

    if(! leer_notas(f, contenedor, canal, pps)){
        destruir_nota_contenedor_t(contenedor);
        return NULL;
    }

    return contenedor;
}


void destruir_note_t(note_t *note){
    free(note);
}

void destruir_nota_contenedor_t(nota_contenedor_t *contenedor){
    destruir_note_t(contenedor->notes);
    free(contenedor);
}



bool leer_notas(FILE *f, nota_contenedor_t *contenedor, char channel, int pps){
    // LECTURA DEL ENCABEZADO:
    formato_t formato;
    uint16_t numero_pistas;
    uint16_t pulsos_negra;

    if(! leer_encabezado(f, &formato, &numero_pistas, &pulsos_negra)) {
        fprintf(stderr, "Fallo lectura encabezado\n");
        return false;
    }


    size_t encendida = 0; //Cuenta la cantidad de note_t encendidas.
    size_t apagada = 0;	//Cuenta la cantidad de note_t apagadas.
    size_t mem = 100; //Para hacer realloc de note en 100 unidades.


    // ITERAMOS LAS PISTAS:
    for(uint16_t pista = 0; pista < numero_pistas; pista++) {
        // LECTURA ENCABEZADO DE LA PISTA:
        uint32_t tamagno_pista;
        if(! leer_pista(f, &tamagno_pista)) {
            fprintf(stderr, "Fallo lectura pista\n");
            return false;
        }

        evento_t evento;
        char canal;
        int longitud;
        double tiempo = 0;

        // ITERAMOS LOS EVENTOS:
        while(1) {
            double delta_tiempo = 0;
            leer_tiempo(f, &delta_tiempo, pps);
            tiempo += delta_tiempo;

            // LECTURA DEL EVENTO:
            uint8_t buffer[EVENTO_MAX_LONG];
            if(! leer_evento(f, &evento, &canal, &longitud, buffer)) {
                fprintf(stderr, "Error leyendo evento\n");
                return false;
            }

            // PROCESAMOS EL EVENTO:
            if(evento == METAEVENTO && canal == 0xF) {
                // METAEVENTO:
                if(buffer[METAEVENTO_TIPO] == METAEVENTO_FIN_DE_PISTA)
                    break;

                descartar_metaevento(f, buffer[METAEVENTO_LONGITUD]);
            }
            else if (evento == NOTA_ENCENDIDA || evento == NOTA_APAGADA) {
                // NOTA:
                nota_t nota;
                signed char octava;
                if(! decodificar_nota(buffer[EVNOTA_NOTA], &nota, &octava)) {
                    fprintf(stderr, "Error leyendo nota\n");
                    return false;
                }

                //GUARDADO DE DATOS EN CONTENEDOR DE NOTES DE 1 CANAL:
                if(channel == canal){
                    if(evento == NOTA_ENCENDIDA && buffer[EVNOTA_VELOCIDAD] != 0){
                	   contenedor->notes[encendida].intensidad = buffer[EVNOTA_VELOCIDAD];
                	   contenedor->notes[encendida].t0 = tiempo;
                	   contenedor->notes[encendida].octava = octava;
                	   contenedor->notes[encendida].nota = codificar_nota(nota);
                	   encendida++;
                    }

                    else if((evento == NOTA_ENCENDIDA && buffer[EVNOTA_VELOCIDAD] == 0) || evento == NOTA_APAGADA){
                	   contenedor->notes[apagada].duracion = tiempo - contenedor->notes[apagada].t0;
                	   apagada++;
                    }

                    if(encendida == mem){
                	    note_t *aux = realloc(contenedor->notes, sizeof(note_t) * 100);
            	        if(aux == NULL){
               	            destruir_nota_contenedor_t(contenedor);
            		        return false;
                	    }

                        contenedor->notes = aux;

                	   mem += 100;
                    }
                }

            }
        }
    }

    contenedor->cant_notas = encendida;

    return true;
}


float leer_frecuencia_nota(note_t n){
    int i;

    nota_t notas[12];

    for(i = 0; i < 12; i++)
        if(! strcmp(n.nota, codificar_nota(notas[i])))
            break;

    return 440 * (pow((1.0) / 2, 4 - n.octava)) * (pow(2, (i - 9) / 12));
}