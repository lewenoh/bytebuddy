//
// Created by js5422 on 15/06/24.
//

#ifndef ARMV8_51_PASS_ONE_H
#define ARMV8_51_PASS_ONE_H
#include "instruction_arr.h"
#include "symbol_table.h"

void first_pass(FILE *inputFile, instruction_array *ia, symbol_table *s, char *lineBuffer);

#endif //ARMV8_51_PASS_ONE_H
