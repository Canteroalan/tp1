#ifndef TRAMO_H
#define TRAMO_H

#include <stdio.h>
#include <stdbool.h>


#include "NOTA.H"
#include "FUNCIONES.H"
#include "SINTETIZADOR.H"

typedef struct _tramo tramo_t;


//ej3.c
double onda(double t, float a, float f, float phi);
void inicializar_muestras(float v[], size_t n);
void imprimir_muestras(const float v[], size_t n, double t0, int f_m);
void muestrear_senoidal(float v[], size_t n, double t0, int f_m, float f, float a);
void muestrear_armonicos(float v[], size_t n, double t0, int f_m, float f, float a, float fa[][2], size_t n_fa);
tramo_t *_tramo_crear(double t0, double tf, int f_m);
void tramo_destruir(tramo_t *t);
tramo_t *tramo_clonar(const tramo_t *t);
tramo_t *tramo_crear_muestreo(double t0, double tf, int f_m, float f, float a, float fa[][2], size_t n_fa);
bool tramo_redimensionar(tramo_t *t, double tf);
bool tramo_extender(tramo_t *destino, const tramo_t *extension);


//tramo.c
double calcular_tf(note_t nota, synt_t *s);
void determina_max_and_min(float *max, float *min, float v);
tramo_t *modulacion(tramo_t *t, synt_t *s);
int16_t *sintetizar_cancion(FILE *midi, FILE *sintetizador, int f_m, size_t *cantidad, char canal, int pps);
float crear_factor_escala(float maximo, float minimo);
int16_t *crear_muestras(tramo_t *t, float v);
void destruir_int16_t(int16_t *v);

#endif