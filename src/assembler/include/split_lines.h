#ifndef SPLIT_LINES_H
#define SPLIT_LINES_H
#include "table_def.h"

void split_lines(FILE *inputFile, instruction_array *ia,char *lineBuffer);
instruction_array *create_empty_instructionArr();
instruction create_instruction(char * instr);
void add_instruction(instruction_array *instructionArray, instruction *instr);
void free_instruction_arr(instruction_array *instructionArray);
void test_ilines();
#endif
