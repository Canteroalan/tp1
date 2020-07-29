#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>



bool escribir_wave(FILE *w){
	char ChunkId[4] = "RIFF";
	char Format[4] = "WAVE";
	char SubChunk1ID[4] = "fmt ";
	uint32_t SubChunk1Size = 16;
	uint16_t AudioFormat = 1;
	uint16_t NumChannels = 1;
	uint16_t BlockAlign = 2;
	uint16_t BitsPerSample = 16;
	char SubChunk2ID[4] = "data";



	if(fwrite(ChunkId, sizeof(char), 4, w) != 4)
		return false;

	//ChunkSize

	if(fwrite(Format, sizeof(char), 4, w) != 4)
		return false;

	if(fwrite(SubChunk1ID, sizeof(char), 4, w) != 4)
		return false;

	if(fwrite(&SubChunk1Size, sizeof(uint32_t), 1, w) != 1)
		return false;

	if(fwrite(&AudioFormat, sizeof(uint16_t), 1, w) != 1)
		return false;

	if(fwrite(&NumChannels, sizeof(uint16_t), 1, w) != 1)
		return false;

	//SampleRate

	//ByteRate

	if(fwrite(&BlockAlign, sizeof(uint16_t), 1, w) != 1)
		return false;

	if(fwrite(&BitsPerSample, sizeof(uint16_t), 1, w) != 1)
		return false;

	if(fwrite(SubChunk2ID, sizeof(char), 4, w) != 4)
		return false;

	//SubChunk2Size

	//Data
	
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