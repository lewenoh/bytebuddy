#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "helperfuncs.h"
#include "dpi_encoder.h"
#include "branch_encoder.h"
#include "sdt_encoder.h"

int main(int argc, char **argv) {
  // .s file read -> Instruction table, Symbol Table
  // For each instruction, classify.
  // Encode each instruction into binary.
  // Write binary to .bin file.

	FILE *inputFile = fopen(argv[1], "r");
	FILE *outputFile = fopen(argv[2], "w");
	char *lineBuffer;
	int instrCount = 0;
	char **instructionLines;

	if (inputFile == NULL || ferror(inputFile)) {
        	fprintf(stderr, "Error opening input file.\n");
        	exit(1);
        } else if (outputFile == NULL || ferror(outputFile)) {
		fprintf(stderr, "Error opening output file.\n");
		exit(1);
	} else { // once input and output file validated
        	instructionLines = split_lines(inputFile, lineBuffer, &instrCount); // splits instructions line by line into line buffer.
        }

	// test for split_lines
	fprintf(outputFile, "%d", instrCount);
	
	for (int i = 0; i < instrCount; i++) {
		printf("BOO\n");
		fprintf(outputFile, "%s\n", instructionLines[i]);
	}

	//first and second pass
//
//	int noInstrs;
//	uint32_t instrs[noInstrs];
//
//	//decode each instruction, and put into instrs
//
//	int instrWrite = fwrite(instrs, 4, noInstrs, outputFile);
//	if (instrWrite < noInstrs){
//		fclose(outputFile);
//		fprintf(stderr, "Error writing to the file.\n");
//	}
//	fclose(outputFile);

// uncomment below if not freed in any function
//	for (int i = 0; i < instrLineIndex; i++) {
//                free(instrLines[i]);
//        }
//        free(instrLines);
	fclose(outputFile);
	return EXIT_SUCCESS;
}

