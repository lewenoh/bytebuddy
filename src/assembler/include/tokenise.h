//
// Created by js5422 on 11/06/24.
//

#ifndef ARMV8_51_TOKENISE_H
#define ARMV8_51_TOKENISE_H
#include "../include/table_def.h"

token_arr *initialise_token_arr();
token_arr *tokenise(char* raw_instr);
int set_mand_args(char instr_identifier);
void skip_space(instruction *raw_instr, int *index);
void process_args(int num_args, instruction c, int *index, instruction raw_instr, token_arr *tokenArr);
#endif //ARMV8_51_TOKENISE_H
