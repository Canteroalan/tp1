#ifndef TRAMO_H
#define TRAMO_H

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    float *v;
    size_t n;
    double t0;
    int f_m;
} tramo_t;


//ej3.c
double onda(double t, float a, float f, float phi);
void inicializar_muestras(float v[], size_t n);
void muestrear_senoidal(float v[], size_t n, double t0, int f_m, float f, float a);
void muestrear_armonicos(float v[], size_t n, double t0, int f_m, float f, float a, const float fa[][2], size_t n_fa);
tramo_t *_tramo_crear(double t0, double tf, int f_m);
void tramo_destruir(tramo_t *t);
tramo_t *tramo_clonar(const tramo_t *t);
tramo_t *tramo_crear_muestreo(double t0, double tf, int f_m, float f, float a, const float fa[][2], size_t n_fa);
bool tramo_redimensionar(tramo_t *t, double tf);
bool tramo_extender(tramo_t *destino, const tramo_t *extension);


//tramo.c
float leer_frecuencia_tramo(note_t *nota);
double calcular_tf(note_t *nota, float td);
float **generar_matriz_armonicos(synt_t synt);
void destruir_matriz(float **r, size_t cantidad_de_columnas);
tramo_t *modulacion(tramo_t *t, synt_t *synt);
tramo_t *sintetizar_cancion(note_t v[],size_t tamagno,synt_t * w ,int fre_mtro);


#endif // TRAMO_H