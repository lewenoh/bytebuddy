//
// Created by js5422 on 15/06/24.
//

#include "../include/instruction_arr.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

instruction_array *create_empty_instructionArr() {
    instruction_array *s = (instruction_array *) malloc(sizeof(instruction_array));
    if (s == NULL) {
        abort();
    }
    s->size = 0;
    s->instructions = NULL;
    return s;
}


instruction create_instruction(char * instr) {
    instruction i = (instruction) malloc(sizeof(char) * (strlen(instr)+1));
    assert(i != NULL);
    strcpy(i, instr);
    i[strlen(instr)] = '\0';
    return i;
}

void add_instruction(instruction_array *instructionArray, instruction *instr) {
    instruction *instruction_arr = (instruction *)realloc(instructionArray->instructions,
                                                          sizeof(instruction) * (instructionArray->size+1));
    if (instruction_arr == NULL) {
        abort();
    }
    instructionArray->instructions = instruction_arr;
    instruction_arr[instructionArray->size] = *instr;
    instructionArray->size ++;
}


void free_instruction_arr(instruction_array *instructionArray) {
    for (int i = 0; i < instructionArray->size; i++) {
        free((instructionArray->instructions[i]));
    }
    free(instructionArray->instructions);
    free(instructionArray);
}
