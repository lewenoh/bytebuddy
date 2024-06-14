#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/tokenise.h"
#include "../include/table_def.h"
#include "../include/testcond.h"
#include "../include/symbol_table.h"

void printarr(token_arr *arr) {
    for (int s = 0; s < MAX_ARGS; s++) {
        for (int j = 0; j < MAX_ARG_LENGTH; j++) {
            printf("%c", (*arr)[s][j]);
        }
        printf("\n");
    }

}

void test_tokeniser() {
    int size = 11;
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
    };
    token_arr *tokenArr;

    for (int i = 0; i < size; i++) {
        tokenArr = tokenise(tests[i]);
        printf("Test %d\n", i);
        printarr(tokenArr);
    }
    free(tokenArr);

}

int main(int argc, char **argv) {
    //test_tokeniser();

    // test_create_symbol();
    test_symbol();

    return EXIT_SUCCESS;
}
