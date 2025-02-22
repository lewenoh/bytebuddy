//
// Created by js5422 on 15/06/24.
//

#include "../include/pass_one.h"
#include "../include/instruction_arr.h"
#include "../include/split_lines.h"
#include "../include/symbol_table.h"
#include "../include/helperfuncs.h"
#include "../include/tokenise.h"
#include "assert.h"
#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


void first_pass(FILE *inputFile, instruction_array *ia, symbol_table *s, char *lineBuffer) {
    // Populates instruction array and symbol table

    // LineBuffer contains the entire .s file.
    // Each instruction is separated by \n
    // Write each line to instruction array.

    // Read whole file so we can start to iterate.
    long fileSize;
    int numChar;
    initial_processing(inputFile, &fileSize, &numChar);
    // allocating suitable amount of space in lineBuffer.
    lineBuffer = (char *) malloc(fileSize + 1);
    assert(lineBuffer != NULL);
    read_whole_file(lineBuffer, numChar, inputFile);
    char *line = strtok(lineBuffer, "\n"); // split the buffer into lines

    int instr_count = 0;
    int real_instr_count = 0;
    // Classify instruction; Add to instruction / symbol table.
    while (line != NULL) {
        // Symbol Table logic goes here.
        int dummy = 0;
        skip_space(&line, &dummy);
        int index = 0;
        instruction curr_instruction = create_instruction(line);
        char * start = curr_instruction;

        while (!isspace(*start) && (*start != ':') ) {
            index++;
            start++;
        }
        char * buffer = (char *)malloc(sizeof(char)*(index+1));
        strncpy(buffer, curr_instruction, index);
        buffer[index] = '\0'; // Ensure null termination
        skip_space(&curr_instruction, &index);


        if (not_label_int(buffer)){
            add_instruction(ia, &curr_instruction);
            real_instr_count ++;
        } else {
            // label
            char address[30] = "#0x";
            char address_num[30];
            sprintf(address_num, "%x", (real_instr_count)*4);
            strcat(address, address_num);
            label_entry *labelEntry = create_entry(buffer, address);
            add_entry(s, labelEntry);
	    free(curr_instruction);
        }

        free(buffer);
        instr_count ++;
        line = strtok(NULL, "\n"); // get the next line
    }
    if (ferror(inputFile)) {
        perror("Error reading file");
    }

    free(lineBuffer);
    fclose(inputFile);
}
