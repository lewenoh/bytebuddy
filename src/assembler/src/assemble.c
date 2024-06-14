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
	FILE *outputFile = fopen(argv[2], "wb");
	char *lineBuffer;

	if (inputFile == NULL || ferror(inputFile)) {
        	fprintf(stderr, "Error opening input file.\n");
        	exit(1);
        } else if (outputFile == NULL || ferror(outputFile)) {
		fprintf(stderr, "Error opening output file.\n");
		exit(1);
	} else { // once input and output file validated
        	char **instructionLines = split_lines(inputFile, lineBuffer); // splits instructions line by line into line buffer.
        }
	
	//first and second pass
	int noinstrs;
	uint32_t instrs[noinstrs];
	//decode each instruction, and put into instrs
	
	int instrwrite = fwrite(instrs, 4, noinstrs, outputFile);
	if (instrwrite<noinstrs){
		fclose (outputfile);
		fprintf(stderr, "Error writing to the file.\n");
	}
	fclose(outputFile);


	return EXIT_SUCCESS;
}
