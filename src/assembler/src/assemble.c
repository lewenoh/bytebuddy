#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/tokenise.h"
#include "../include/table_def.h"
#include "../include/testcond.h"

#define test1 "and x0, x0, x0";

void printarr(token_arr *arr) {
    for (int s = 0; s < 5; s++) {
        for (int j = 0; j < 30; j++) {
            printf("%c", (*arr)[s][j]);
        }
        printf("\n");
    }

}

int main(int argc, char **argv) {
    int size = 4;
    char tests[][30] = {"and x0, x0, x0",
                        "add x0, x0, #0x18",
                        "add x0, x0, #0x1, lsl #12",
                        "madd x18, x12, x24, x18"

    };
    token_arr *tokenArr;

    for (int i = 0; i < size; i++) {
        tokenArr = tokenise(tests[i]);
        printf("Test %d\n", i);
        printarr(tokenArr);
    }


    free(tokenArr);


  return EXIT_SUCCESS;
}
