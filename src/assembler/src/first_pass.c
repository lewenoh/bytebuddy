//
// Created by js5422 on 14/06/24.
//

#include "../include/first_pass.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

instruction_array *create_example_instructionArray() {
    instruction_array *ia = create_empty_instructionArr();
    instruction i, i1;
    i = create_instruction("b.eq next");
    add_instruction(ia, &i);
    i1 = create_instruction("next:");
    add_instruction(ia, &i1);
    return ia;
}

void iterate_instruction(instruction_array *instructionArray) {
    for (int i = 0; i < instructionArray->size; i++) {
        instruction instr = instructionArray->instructions[i];


        printf("Instruction %d: ", i);
        for (int j = 0; j < strlen(instr); j++) {
            printf("%c ", instr[j]);
        }
        printf("\n");
    }
}

void first_pass_test(instruction_array *instructionArray) {

    for (int i=0; i < instructionArray->size; i++) {
        int index=0;
        // // Find index after instruction identifer.
        instruction instr = instructionArray->instructions[i];
        while (!isspace(instr[index])) {
            index++;
        }

        // Buffer is needed for classification.
        char * buffer = (char *)malloc(sizeof(char)*(index+1));
        strncpy(buffer, (instructionArray->instructions[i]), index);
        buffer[index] = '\0'; // Ensure null termination
        printf("Buffer: %s\n", buffer);
        buffer[i] = '\0';
        free(buffer);
    }
    free_instruction_arr(instructionArray);
}

void first_pass_prior(instructionlines instrLines, int *num_instr, symbol_table *s) {
    int count = 0;
    for (int i = 0; i < *num_instr; i ++) {
        int index = 0;
        instruction instr = instrLines[i];
        // // Find index after instruction identifer.

        while (!isspace(*instr) && (*instr != ':') ) {
            index++;
            instr++;
        }
        char * buffer = (char *)malloc(sizeof(char)*(index+1));

        strncpy(buffer, instrLines[i], index);
        buffer[index] = '\0'; // Ensure null termination
        if (
                strcmp(buffer, "cmp") == 0 ||
                strcmp(buffer, "cmn") == 0 ||
                strcmp(buffer, "neg") == 0 ||
                strcmp(buffer, "negs") == 0 ||
                strcmp(buffer, "tst") == 0 ||
                strcmp(buffer, "movk") == 0 ||
                strcmp(buffer, "movn") == 0 ||
                strcmp(buffer, "movz") == 0 ||
                strcmp(buffer, "mov") == 0 ||
                strcmp(buffer, "mvn") == 0 ||
                strcmp(buffer, "madd") == 0 ||
                strcmp(buffer, "msub") == 0 ||
                strcmp(buffer, ".int") == 0 ||
                strcmp(buffer, "br") == 0 ||
                strcmp(buffer, "b") == 0 ||
                strcmp(buffer, "b.eq") == 0 ||
                strcmp(buffer, "b.ne") == 0 ||
                strcmp(buffer, "b.ge") == 0 ||
                strcmp(buffer, "b.lt") == 0 ||
                strcmp(buffer, "b.gt") == 0 ||
                strcmp(buffer, "b.le") == 0 ||
                strcmp(buffer, "b.al") == 0 ||
                strcmp(buffer, "ldr") == 0 ||
                strcmp(buffer, "str")==0 ||
                strcmp(buffer, "add")==0 ||
                strcmp(buffer, "adds")==0 ||
                strcmp(buffer, "sub") == 0 ||
                strcmp(buffer, "subs")==0 ||
                strcmp(buffer, "and")==0 ||
                strcmp(buffer, "ands")==0 ||
                strcmp(buffer, "bic")==0 ||
                strcmp(buffer, "bics")==0 ||
                strcmp(buffer, "eor")==0 ||
                strcmp(buffer, "orr")==0 ||
                strcmp(buffer, "eon")==0 ||
                strcmp(buffer, "orn")==0) {
            count++;
            free(buffer);
            continue;

        } else {
            // label
            char address[20] = "#0x";
            char address_num[17];
            sprintf(address_num, "%x", (i+1)*4);
            strcat(address, address_num);
            label_entry *labelEntry = create_entry(buffer, address);
            add_entry(s, labelEntry);
        }
        free(buffer);
    }
    *num_instr = count;
}
