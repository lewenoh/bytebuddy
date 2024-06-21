#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/tokenise.h"
#include <stdint.h>
#include "../include/pass_one.h"
#include "../include/helperfuncs.h"
#include "../include/dpi_encoder.h"
#include "../include/branch_encoder.h"
#include "../include/sdt_encoder.h"


int main(int argc, char **argv) {
    //     .s file read -> Instruction table, Symbol Table
    //     For each instruction, classify.
    //     Encode each instruction into binary.
    //     Write binary to .bin file.
    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[2], "wb");
    char *lineBuffer = NULL;
    if (inputFile == NULL || ferror(inputFile)) {
        fprintf(stderr, "Error opening input file.\n");
        exit(1);
    } else if (outputFile == NULL || ferror(outputFile)) {
        fprintf(stderr, "Error opening output file.\n");
        exit(1);
    } else { // once input and output file validated

        instruction_array *ia = create_empty_instructionArr();
        symbol_table *sym = create_empty_table();
        first_pass(inputFile, ia, sym, lineBuffer);

        uint32_t instrs[ia->size];
        for (int i = 0; i < ia->size; i++) {
            token_arr *tokenArr;
            tokenArr = tokenise(ia->instructions[i], sym);
            //Depending on type do something different.
            if (is_dpi((*tokenArr)[0])) {
                instrs[i] = dpi_encoder(*tokenArr);
                //tokenised instruction is the char instruction[6][30]
            } else if (is_branch((*tokenArr)[0])) {
                instrs[i] = branch_encoder((i*4), *tokenArr);
            } else if (is_sdt((*tokenArr)[0])) {
                instrs[i] = sdt_encoder((i*4), *tokenArr);
            } else if (is_special((*tokenArr)[0])) {
		instrs[i] = readimm((*tokenArr)[1]);
            }
	    free_token_arr(tokenArr);
        }

        //decode each instruction, and put into instrs
        int instrWrite = fwrite(instrs, 4, ia->size, outputFile);
        if (instrWrite < ia->size){
            fclose(outputFile);
            fprintf(stderr, "Error writing to the file.\n");
        }
        fclose(outputFile);
        free_instruction_arr(ia);
	free_symbol_table(sym);
        return EXIT_SUCCESS;
    }
}

