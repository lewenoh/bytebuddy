#include <stdio.h>
#include <stdlib.h>
#include "binary_load.h"
#include "processor_def.h"
#include "binary_to_hex.h"
#define MEMORY_SIZE 524288

int binary_load(struct processor p, FILE *inputFile, FILE *outputFile) {

	if (fseek(inputFile, 0, SEEK_END) == -1) {
		fclose(inputFile);
		fprintf(stderr, "Error seeking to end of file.\n");
		return 1; // seek failure
	}

	// now at end of file
	long fileSize = ftell(inputFile); // in bytes
	int numInstr = fileSize / 4; // each instruction is 32 bits = 4 bytes
	rewind(inputFile); // return to start

	int instrRead = fread(p.memory, 4, numInstr, inputFile);

	if (instrRead < numInstr) {
		fclose(inputFile);
		fprintf(stderr, "Error reading from file.\n");

		for (int i = 0; i < MEMORY_SIZE; i++) {
			p.memory[i] = 0x0; // setting memory to 0 if there was an error.
		}

		return 1;
	} else { // successful read
		for (int i = 0; i < MEMORY_SIZE; i++) {
			p.memory[i] = binaryToHex(p.memory[i]); // covert raw binary 32 bits into hex at each memory location
		}
	}

	return 0;

}
