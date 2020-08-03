#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

#include"tramo.h"

#define PI 3.141592653589793
#define FASE 0



double onda(double t,float a , float f,float phi ){
        return  a*sin(2*PI*f*t+phi);
}

void inicializar_muestras(float v[],size_t n){
        for(int i=0;i<n;i++)
                v[i]=0;
}

void imprimir_muestras(const float v[],size_t n,double t0,int f_m){
        double t;
        for(int i=0;i<n;i++){
                t=t0+(double)i/f_m;
                printf("%f,%f\n",t,v[i]);
        }
}

void muestrear_senoidal(float v[],size_t n,double t0,int f_m,float f,float a){
        double t ;
        for(int i=0;i<n;i++){
                t= t0 + (double)i/f_m;
                v[i] += onda(t,a,f,FASE);
        }
}

void muestrear_armonicos(float v[],size_t n,double t0,int f_m,float f,float a,const float fa[][2],size_t n_fa){
        float frecuencia;
        float amplitud;
        inicializar_muestras(v,n);
        for(int i=0;i<n_fa;i++){
                frecuencia=f*fa[i][0];
                amplitud=a*fa[i][1];
                muestrear_senoidal(v,n,t0,f_m,frecuencia,amplitud);
        }
}

tramo_t * _tramo_crear(double t0,double tf,int f_m){
        int n=f_m*(tf-t0);
        tramo_t *tramo=malloc(sizeof(tramo_t));

        if(tramo==NULL){
                printf("fallo en el malloc de la linea 59\n");
                return NULL;
        }

        float *muestras=malloc(n*sizeof(float));

        if(tramo==NULL){
                printf("fallo en el malloc de la linea 66\n");
                return NULL;
        }

        tramo_t r={muestras,n,t0,f_m};
        *tramo=r;
        return tramo;
}

void tramo_destruir(tramo_t * t){
        free(t->v);
        free(t);
}

tramo_t * tramo_clonar(const tramo_t *t){
        double t_f=(t->t0)+(t->n)/(t->f_m);
        tramo_t * clon=_tramo_crear(t->t0,t_f,t->f_m);
        for(size_t i=0;i<t->n;i++)
                clon->v[i]=t->v[i];
        return clon;
}

tramo_t * tramo_crear_muestreo(double t0,double tf,int f_m,float f,float a,const float fa[][2],size_t n_fa){
        tramo_t * muestreo= _tramo_crear(t0,tf,f_m);
        muestrear_armonicos(muestreo->v,muestreo->n,t0,f_m,f,a,fa,n_fa);
        return muestreo;
}

bool tramo_redimensionar(tramo_t * t,double tf){
        int new_n=(t->f_m)*(tf-(t->t0));
        float * aux=realloc((t->v),new_n*sizeof(float));
        if(aux==NULL)
                return false;

        t->v=aux;
        if((t->n)<new_n){
                for(size_t i=(t->n);i<new_n;i++)
                        aux[i]=0;
        }
        t->n=new_n;
        return true;
}

bool tramo_extender(tramo_t *destino,const tramo_t *extension){
        if((destino->t0 > extension->t0))
                return false;
        double tf_dest=(destino->t0)+(double)(destino->n)/(destino->f_m);
        double tf_exts=(extension->t0)+(double)(extension->n)/(extension->f_m);

        if(tf_dest<tf_exts)
                tramo_redimensionar(destino,tf_exts);

        for(size_t i=0;i<(destino->n);i++){
                if(i>(extension->t0*extension->f_m) && i<(tf_exts*extension->f_m))
                        destino->v[i]  =  destino->v[i] + extension->v[(i-(int)(extension->t0*extension->f_m))];

                continue;
        }
        return true;
}


