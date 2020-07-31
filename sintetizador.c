#include<stdio.h>
#include<stdint.h>

double constant(){
	return 1;
}

double linear(double t0,double t){
	return t/t0;
}

double sin(double t,float a,float f){
	return 1+a*sin(f*t);
}




