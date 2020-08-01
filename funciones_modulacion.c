#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#include "FUNCIONES.h"

typedef float (*funcion_t)(double, float [3]);

struct traduccion_funcion {
	float (*funcion)(double, float [3]);
	char *cadena;
};

static const funcion_t funciones[] = {
    {modulacion_constante, "CONSTANT"},
    {modulacion_linear, "LINEAR"},
    {modulacion_inlinear, "INVLINEAR"},
    {modulacion_seno, "SIN"},
    {modulacion_exponencial, "EXP"},
    {modulacion_invexponencial, "INVEXP"},
    {modulacion_quartcoseno, "QUARTCOS"},
    {modulacion_quartseno, "QUARTSIN"},
    {modulacion_halfcoseno, "HALFCOS"},
    {modulacion_halfseno, "HALFSIN"},
    {modulacion_logaritmo, "LOG"},
    {modulacion_invlogaritmo, "INVLOG"},
    {modulacion_tri, "TRI"},
    {modulacion_pulsos, "PULSES"}
};




float modulacion_constante(double t, float params[3]) {
    return 1;
}

float modulacion_linear(double t, float params[3]) {
    return 1;
}

float modulacion_inlinear(double t, float params[3]) {
    return 1;
}

float modulacion_seno(double t, float params[3]) {
    return 1;
}

float modulacion_exponencial(double t, float params[3]) {
    return 1;
}

float modulacion_invexponencial(double t, float params[3]) {
    return 1;
}

float modulacion_quartcoseno(double t, float params[3]) {
    return 1;
}

float modulacion_quartseno(double t, float params[3]) {
    return 1;
}

float modulacion_halfseno(double t, float params[3]) {
    return 1;
}

float modulacion_halfcoseno(double t, float params[3]) {
    return 1;
}

float modulacion_logaritmo(double t, float params[3]) {
    return 1;
}

float modulacion_invlogaritmo(double t, float params[3]) {
    return 1;
}

float modulacion_tri(double t, float params[3]) {
    return 1;
}

float modulacion_pulsos(double t, float params[3]) {
    return 1;
}






