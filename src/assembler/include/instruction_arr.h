//
// Created by js5422 on 15/06/24.
//

#ifndef ARMV8_51_INSTRUCTION_ARR_H
#define ARMV8_51_INSTRUCTION_ARR_H


typedef char * instruction;
typedef struct {
    int size;
    instruction * instructions;
} instruction_array;

instruction_array *create_empty_instructionArr();
instruction create_instruction(char * instr);
void add_instruction(instruction_array *instructionArray, instruction *instr);
void free_instruction_arr(instruction_array *instructionArray);

#endif //ARMV8_51_INSTRUCTION_ARR_H
