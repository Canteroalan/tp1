
#include <stdio.h>
#include<stdlib.h>


int main (int argc,char * argv[]){
	if(argc != 2){
		fprintf(stderr,"funciono con dos argumentos\n");
		return 1;
	}
	printf("%s\n",argv[1]);
	return 0;
}
