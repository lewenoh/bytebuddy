//
// Created by js5422 on 11/06/24.
//

#ifndef ARMV8_51_TOKENISE_H
#define ARMV8_51_TOKENISE_H
#include "../include/table_def.h"
#include "../include/symbol_table.h"
#include <stdbool.h>
#include "../include/instruction_arr.h"
#define MAX_ARGS 6
#define MAX_ARG_LENGTH 30
typedef char token_arr[MAX_ARGS][MAX_ARG_LENGTH];
token_arr *initialise_token_arr();
token_arr *tokenise(char* raw_instr, symbol_table *symbolTable);
void skip_space(instruction *raw_instr, int *index);
bool process_args(int num_args, instruction *pc, int *index, char delim,
                  instruction raw_instr, token_arr *tokenArr, int arg_index);
void process_branch_args(instruction *pc, int *index, instruction raw_instr, token_arr *tokenArr,
                         symbol_table symbolTable);
#endif //ARMV8_51_TOKENISE_H
