#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/tokenise.h"
#include "../include/first_pass.h"


void printarr(token_arr *arr) {
    for (int s = 0; s < MAX_ARGS; s++) {
        for (int j = 0; j < MAX_ARG_LENGTH; j++) {
            printf("%c", (*arr)[s][j]);
        }
        printf("\n");
    }
}

void test_tokeniser() {
    int size = 1;
    /*
    "and x0, x0, x0",
    "add x0, x0, #0x18",
    "add x0, x0, #0x1, lsl #12",
    "madd x18, x12, x24, x18",
    "str x2, [x9, #129]!",
    "str w24, [x13, x9]",
    "str x25, [x11], #239",
    "str x16, [x19], #-62",
    "str x2, [x9, #129]",
    "ldr w17, [x15, x4]",
    "ldr x1, 0x10",
     */
    char tests[][30] = {
            "b.eq next"
    };
    symbol_table *sym = create_example_symbol_table();
    token_arr *tokenArr;

    for (int i = 0; i < size; i++) {
        tokenArr = tokenise(tests[i], sym);
        printf("Test %d\n", i);
        printarr(tokenArr);
    }
    free(tokenArr);
    free_symbol_table(sym);
}

//void test_first_pass() {
//    instruction_array *ia = create_example_instructionArray();
//    first_pass_test(ia);
//}

void test_create_empty_ia() {
    instruction_array *ia = create_empty_instructionArr();
    free_instruction_arr(ia);
}

void test_add_instruction_ia(char * instruction_text) {
    instruction_array *ia = create_empty_instructionArr();
    if (ia == NULL) {
        free(ia);
        abort();
    }
    instruction i;
    i = create_instruction(instruction_text);
    add_instruction(ia, &i);
    free_instruction_arr(ia);
}

void test_create_example_ia() {
    instruction_array *ia;
    ia = create_example_instructionArray();
    free_instruction_arr(ia);
}

void test_first_pass() {
    char * i1 = "next:";
    char * i2 = "add x0, x0, x0";
    char * i3 = "bumbaclat:";
    char * i4 = "str x25, [x11], #239";
    int i_num = 4;

    // Allocate memory for an array of 2 pointers to char
    instructionlines ilines = (instructionlines)malloc(i_num * sizeof(char *));
    if (ilines == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        abort();
    }

    // Initialize the first string
    ilines[0] = (char *)malloc((strlen(i1) + 1) * sizeof(char)); // +1 for the null terminator
    if (ilines[0] == NULL) {
        fprintf(stderr, "Memory allocation for first string failed\n");
        free(ilines); // Free the previously allocated memory
        abort();
    }
    strcpy(ilines[0], i1);

    // Initialize the second string
    ilines[1] = (char *)malloc((strlen(i2) + 1) * sizeof(char)); // +1 for the null terminator
    if (ilines[1] == NULL) {
        fprintf(stderr, "Memory allocation for second string failed\n");
        free(ilines[0]); // Free the previously allocated memory
        free(ilines);
        abort();
    }
    strcpy(ilines[1], i2);

    ilines[2] = (char *)malloc((strlen(i3) + 1) * sizeof(char)); // +1 for the null terminator
    if (ilines[2] == NULL) {
        fprintf(stderr, "Memory allocation for second string failed\n");
        free(ilines[0]); // Free the previously allocated memory
        free(ilines);
        abort();
    }
    strcpy(ilines[2], i3);

    ilines[3] = (char *)malloc((strlen(i4) + 1) * sizeof(char)); // +1 for the null terminator
    if (ilines[3] == NULL) {
        fprintf(stderr, "Memory allocation for second string failed\n");
        free(ilines[0]); // Free the previously allocated memory
        free(ilines);
        abort();
    }
    strcpy(ilines[3], i4);

    symbol_table *s = create_empty_table();
    int num_instr = i_num;
    first_pass(ilines, &num_instr, s);

    // Free the allocated memory
    for (int i = 0; i < i_num; i++) {
        free(ilines[i]);
    }
    free(ilines);
    free_symbol_table(s);
}

int main(int argc, char **argv) {
//    test_create_empty_ia();
//    test_create_symbol();
//    test_create_example_ia();
    test_first_pass();
    return EXIT_SUCCESS;
}
