#include <stdio.h>
#include <stdint.h>


#include "ej5.h"
#include "ej4.h"

#define METAEVENTO_FIN_DE_PISTA 0x2F
#define EVENTO_MAX_LONG 10

enum {EVNOTA_NOTA, EVNOTA_VELOCIDAD};
enum {METAEVENTO_TIPO, METAEVENTO_LONGITUD};

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Uso:\n\t%s <archivo.mid>\n", argv[0]);
        return 1;
    }

    // APERTURA DE ARCHIVO:
    FILE *f = fopen(argv[1], "rb");
    if(f == NULL) {
        fprintf(stderr, "No se pudo abrir \"%s\"\n", argv[1]);
        return 1;
    }

    // LECTURA DEL ENCABEZADO:
    formato_t formato;
    uint16_t numero_pistas;
    uint16_t pulsos_negra;

    if(! leer_encabezado(f, &formato, &numero_pistas, &pulsos_negra)) {
        fprintf(stderr, "Fallo lectura encabezado\n");
        fclose(f);
        return 1;
    }

    printf("Encabezado:\n\tFormato: %s\n\tNumero de pistas: %d\n\tPulsos por negra: %d\n", codificar_formato(formato), numero_pistas, pulsos_negra);

    // ITERAMOS LAS PISTAS:
    for(uint16_t pista = 0; pista < numero_pistas; pista++) {
        // LECTURA ENCABEZADO DE LA PISTA:
        uint32_t tamagno_pista;
        if(! leer_pista(f, &tamagno_pista)) {
            fprintf(stderr, "Fallo lectura pista\n");
            fclose(f);
            return 1;
        }

      	printf("Pista %d:\n\tTama~no: %d\n", pista, tamagno_pista);

        evento_t evento;
        char canal;
        int longitud;
        uint32_t tiempo = 0;

        // ITERAMOS LOS EVENTOS:
        while(1) {
            uint32_t delta_tiempo;
            leer_tiempo(f, &delta_tiempo);
            tiempo += delta_tiempo;
            printf("[%d] ", tiempo);

            // LECTURA DEL EVENTO:
            uint8_t buffer[EVENTO_MAX_LONG];
            if(! leer_evento(f, &evento, &canal, &longitud, buffer)) {
                fprintf(stderr, "Error leyendo evento\n");
                fclose(f);
                return 1;
            }

            printf("Evento: %s, Canal: %d", codificar_evento(evento), canal);

            // PROCESAMOS EL EVENTO:
            if(evento == METAEVENTO && canal == 0xF) {
                // METAEVENTO:
                if(buffer[METAEVENTO_TIPO] == METAEVENTO_FIN_DE_PISTA) {
                    putchar('\n');
                    printf("Final de la pista %d.\n", pista);
                    break;
                }

                descartar_metaevento(f, buffer[METAEVENTO_LONGITUD]);
            }
            else if (evento == NOTA_ENCENDIDA || evento == NOTA_APAGADA) {
                // NOTA:
                nota_t nota;
                signed char octava;
                if(! decodificar_nota(buffer[EVNOTA_NOTA], &nota, &octava)) {
                    fprintf(stderr, "Error leyendo nota\n");
		    fclose(f);
                    return 1;
                }
                printf(", Nota: %s, Octava: %d, Velocidad: %d", codificar_nota(nota), octava, buffer[EVNOTA_VELOCIDAD]);
            }
            putchar('\n');
        }
    }

    printf("Procesamiento finalizado.\n");
    fclose(f);

    return 0;
}



