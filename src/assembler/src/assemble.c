#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../include/helperfuncs.h"
#include "../include/dpi_encoder.h"
#include "../include/branch_encoder.h"
#include "../include/sdt_encoder.h"
#include "../include/table_def.h"
#include "../include/split_lines.h"


int main(int argc, char **argv) {
    //     .s file read -> Instruction table, Symbol Table
    //     For each instruction, classify.
    //     Encode each instruction into binary.
    //     Write binary to .bin file.
    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[2], "w");
    char *lineBuffer = NULL;

    instructionLinesType * instructionlines;
    instruction_array *ia = create_empty_instructionArr();

    if (inputFile == NULL || ferror(inputFile)) {
        fprintf(stderr, "Error opening input file.\n");
        exit(1);
    } else if (outputFile == NULL || ferror(outputFile)) {
        fprintf(stderr, "Error opening output file.\n");
        exit(1);
    } else { // once input and output file validated
        split_lines(inputFile, ia, lineBuffer); // splits instructions line by line into line buffer.
    }

    // test for split_lines
    fprintf(outputFile, "%d", ia->size);

    for (int i = 0; i < ia->size; i++) {
        printf("BOO\n");
        fprintf(outputFile, "%s\n", (ia->instructions)[i]);
    }

//    first and second pass
    uint32_t instrs[ia->size];

    //decode each instruction, and put into instrs
    int instrWrite = fwrite(instrs, 4, ia->size, outputFile);
    if (instrWrite < ia->size){
        fclose(outputFile);
        fprintf(stderr, "Error writing to the file.\n");
    }
    fclose(outputFile);
    free_instruction_arr(ia);

	return EXIT_SUCCESS;
}

