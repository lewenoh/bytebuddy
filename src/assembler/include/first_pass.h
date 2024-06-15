//
// Created by js5422 on 14/06/24.
//

#ifndef ARMV8_51_FIRST_PASS_H
#define ARMV8_51_FIRST_PASS_H
#include "table_def.h"
#include "../include/symbol_table.h"
void test_add_instruction_ia(char * instruction_text);
typedef char ** instructionlines;

typedef struct {
    int size;
    instruction *instructions;
} instruction_array;
void first_pass_test(instruction_array *instructionArray);
void add_instruction(instruction_array *instructionArray, instruction *instruction_entry);
instruction_array *create_empty_instructionArr();
instruction_array *create_example_instructionArray();
void free_instruction_arr(instruction_array *instructionArray);
instruction create_instruction(char * instr);
void first_pass(instructionlines instrLines, int *num_instr, symbol_table *s);

#endif //ARMV8_51_FIRST_PASS_H
