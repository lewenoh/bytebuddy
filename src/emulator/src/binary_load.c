#include <stdio.h>
#include <stdlib.h>
#include "binary_load.h"
#define STARTING_ADDRESS 0x0

int binary_load(FILE *inputFile, FILE *outputFile) {

	if (fseek(inputFile, 0, SEEK_END) == -1) {
		fclose(inputFile);
		printf("Error seeking to end of file.");
		return 1; // seek failure
	}

	// now at end of file
	long fileSize = ftell(inputFile); // in bytes
	int numElems = fileSize / 4; // each instruction is 32 bits = 4 bytes
	rewind(inputFile); // return to start 

	if (fread(STARTING_ADDRESS, 4, numElems, inputFile) < numElems) {
		fclose(inputFile);
		printf("Error reading from file.");
		return 1;
	} else {
		
