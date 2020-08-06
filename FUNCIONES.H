#ifndef FUNCIONES_H
#define FUNCIONES_H

//funciones_modulacion.c
float modulacion_constante(double t, float params[3]);
float modulacion_linear(double t, float params[3]);
float modulacion_invlinear(double t, float params[3]);
float modulacion_seno(double t, float params[3]);
float modulacion_exponencial(double t, float params[3]);
float modulacion_invexponencial(double t, float params[3]);
float modulacion_quartcoseno(double t, float params[3]);
float modulacion_quartseno(double t, float params[3]);
float modulacion_halfseno(double t, float params[3]);
float modulacion_halfcoseno(double t, float params[3]);
float modulacion_logaritmo(double t, float params[3]);
float modulacion_invlogaritmo(double t, float params[3]);
float modulacion_tri(double t, float params[3]);
float modulacion_pulsos(double t, float params[3]);

const float modula_funcion(char *s, float parametros[3], double tiempo);

#endif
