#ifndef TRAMO_H
#define TRAMO_H

#include<stdio.h>
#include<stdbool.h>

typedef struct {
    float *v;
    size_t n;
    double t0;
    int f_m;
} tramo_t;


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



#endif // TRAMO_H