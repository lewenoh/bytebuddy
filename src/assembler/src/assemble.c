#include <stdlib.h>

int main(int argc, char **argv) {
  // .s file read -> Instruction table, Symbol Table
  // For each instruction, classify.
  // Encode each instruction into binary.
  // Write binary to .bin file.

	FILE *inputFile = fopen(argv[1], "r");
	FILE *outputFile = fopen(argv[2], "w");
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

	return EXIT_SUCCESS;
}
