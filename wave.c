#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>



bool escribir_wave(FILE *w, size_t n, int f_m){
	char chunk_id[4] = "RIFF";
	uint32_t chunk_size = 36 + 2 * n; //falta n.
	char format[4] = "WAVE";
	char sub_chunk1_id[4] = "fmt ";
	uint32_t sub_chunk1_size = 16;
	uint16_t audio_format = 1;
	uint16_t num_channels = 1;
	uint32_t sample_rate = f_m; //frecuencia que leemos de argumentos.
	uint32_t byte_rate = 2 * sample_rate;
	uint16_t block_align = 2;
	uint16_t bits_per_sample = 16;
	char sub_chunk2_id[4] = "data";
	uint32_t sub_chunk2_size = 2 * n;
	//int16_t data[n]; me la dan en los parametros. Secuencia de n muestras.



	if(fwrite(chunk_id, sizeof(char), 4, w) != 4)
		return false;

	if(fwrite(&chunk_size, sizeof(uint32_t), 1, w) != 1)
		return false;

	if(fwrite(format, sizeof(char), 4, w) != 4)
		return false;

	if(fwrite(sub_chunk1_id, sizeof(char), 4, w) != 4)
		return false;

	if(fwrite(&sub_chunk1_size, sizeof(uint32_t), 1, w) != 1)
		return false;

	if(fwrite(&audio_format, sizeof(uint16_t), 1, w) != 1)
		return false;

	if(fwrite(&num_channels, sizeof(uint16_t), 1, w) != 1)
		return false;

	if(fwrite(&sample_rate, sizeof(uint32_t), 1, w) != 1)
		return false;

	if(fwrite(&byte_rate, sizeof(uint32_t), 1, w) != 1)
		return false;

	if(fwrite(&block_align, sizeof(uint16_t), 1, w) != 1)
		return false;

	if(fwrite(&bits_per_sample, sizeof(uint16_t), 1, w) != 1)
		return false;

	if(fwrite(sub_chunk2_id, sizeof(char), 4, w) != 4)
		return false;

	if(fwrite(&sub_chunk2_size, sizeof(uint32_t), 1, w) != 1)
		return false;

	if(fwrite(data, sizeof(int16_t), n, w) != n)
		return false;
	
	return true;
}



int main(int argc, char *argv[]){
	FILE *w = fopen(argv[1], "wb");
	if(w == NULL){
		fclose(NULL);
		return 1;
	}

	if(! escribir_wave(w)){
		fclose(w);
		return 1;
	}

	fclose(w);

	return 0;
}