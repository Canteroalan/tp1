#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>


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

bool leer_notas(FILE *f, note_t *note, size_t *cant_notas) {

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
    size_t mem = 20; //Para hacer realloc de note en 20 unidades.


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
            leer_tiempo(f, &delta_tiempo);
            tiempo += delta_tiempo;
            printf("[%f] ", tiempo);

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

                //GUARDADO DE DATOS DE NOTE:
                if(evento == NOTA_ENCENDIDA && buffer[EVNOTA_VELOCIDAD] != 0){
                	note[encendida].intensidad = buffer[EVNOTA_VELOCIDAD];
                	note[encendida].t0 = tiempo;
                	note[encendida].octava = octava;
                	note[encendida].nota = codificar_nota(nota);
                	encendida++;
                }

                if((evento == NOTA_ENCENDIDA && buffer[EVNOTA_VELOCIDAD] == 0) || evento == NOTA_APAGADA){
                	note[apagada].duracion = tiempo - note[apagada].t0;
                	apagada++;
                }

                if(encendida == mem){
                	note_t *aux = realloc(note, sizeof(note_t) * 20);
                	if(aux == NULL){
                		free(note);
                		return false;
                	}

                	mem += 20;
                }

            }
        }
    }

    for(size_t i = 0; i < encendida; i++)
    	printf("Nota[%zd]: intensidad = %f, t0 = %f, duracion = %d, octava = %d, nota = %s\n", i, note[encendida].intensidad, note[encendida].t0, note[encendida].duracion, note[encendida].octava, note[encendida].nota);

    *cant_notas = encendida;

    return true;
}

void destruir_note_t(note_t *note){
    free(note);
}
