#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


char **split(const char * s, const int * anchos, size_t ncampos);
void destruir_lineas(char **lineas, size_t n);
void imprimir_lineas(char **ss, size_t n);

int main(void){
    size_t n = 3;
    int anchos[3] = {10, 4, 6};
    char s[100] = "algoritmos9511essaya";
    char **ss = split(s, anchos, n);
    if(ss == NULL){
        return 1;
    }
    imprimir_lineas(ss, n);
    destruir_lineas(ss, n);
    return 0;
}


char **split(const char * s, const int * anchos, size_t ncampos){

    size_t recorrido = 0;
    char **ss = malloc(sizeof(char *) * ncampos);
    if(ss == NULL){
        return NULL;
    }


    for (size_t i = 0; i < ncampos; i++) {
        ss[i] = malloc(sizeof(char) * (anchos[i] + 1));
        if(ss[i] == NULL){
            destruir_lineas(ss, i);
            return NULL;
        }

        strncpy(ss[i], s+recorrido, anchos[i]);
        ss[i][anchos[i]] = '\0';
        recorrido += anchos[i];
    }

    return ss;
}


void destruir_lineas(char **lineas, size_t n){
    for(size_t i = 0; i < n; i++){
        free(lineas[i]);
    }
    free(lineas);
}

void imprimir_lineas(char **ss, size_t n){
	for(size_t i = 0; i < n; i++){
		printf("%s\n", ss[i]);
	}
}
