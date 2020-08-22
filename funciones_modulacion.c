#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#include "FUNCIONES.H"

#define PI 3.141592653589793

typedef float (*funcion_t)(double, float [3]);

struct traduccion_funcion {
	float (*funcion)(double, float [3]);
	char *cadena;
};

static const struct traduccion_funcion funciones[] = {
    {modulacion_constante, "CONSTANT"},
    {modulacion_linear, "LINEAR"},
    {modulacion_invlinear, "INVLINEAR"},
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
	return t / params[0];
}

float modulacion_invlinear(double t, float params[3]) {
	float n = 1 - (t / params[0]);
	
	if(n > 0){
		return n;
	}
	return 0; 
}

float modulacion_seno(double t, float params[3]) {
	return 1 + (params[0] * sin(params[1] * t));
}

float modulacion_exponencial(double t, float params[3]) {
	return exp((5 * (t - params[0])) / params[0]);
}

float modulacion_invexponencial(double t, float params[3]) {
	return exp((- (5 * t)) / params[0]);
}

float modulacion_quartcoseno(double t, float params[3]) {
	return cos((PI * t) / (2 * params[0]));
}

float modulacion_quartseno(double t, float params[3]) {
	return sin((PI * t) / (2 * params[0]));
}

float modulacion_halfcoseno(double t, float params[3]) {
	return (1 + cos((PI * t) / params[0])) / 2;
}

float modulacion_halfseno(double t, float params[3]) {
	return (1 + sin(PI * ((t / params[0]) - (1.0 / 2.0)))) / 2;
}

float modulacion_logaritmo(double t, float params[3]) {
	return log10((9 * t) / params[0] + 1);
}

float modulacion_invlogaritmo(double t, float params[3]) {
	if(t < params[0])
		return log10((((-9) * t) / params[0]) + 10);
	
	return 0;
}

float modulacion_tri(double t, float params[3]) {
   	if(t < params[1]){
		return ((t * params[2]) / params[1]);
	}
    return (((t - params[1]) / (params[1] - params[0])) * (params[2] - 1)) + params[2];
}

float modulacion_pulsos(double t, float params[3]) {
	float p = ((t / params[0]) - floor(t / params[0])) * params[0];
	float r = fabs(((1 - params[2]) / params[1]) * (p - params[0] + params[1])) + params[2];
	
	if(r < 1)
		return r;
    
    return 1;
}


const float modula_funcion(char *s, float parametros[3], double tiempo){
	size_t i = 0;

	while(strcmp(s, funciones[i].cadena))
		i++;

	return funciones[i].funcion(tiempo, parametros);
}

