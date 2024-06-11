//
// Created by js5422 on 11/06/24.
//

#include "../include/tokenise.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

token_arr *tokenise_instruction(char* raw_instr) {

    // Initialise tokenised array. Default is '\0' char.
    token_arr *tokenised = malloc(sizeof(token_arr));
    if (tokenised == NULL) {
        free(tokenised);
        abort();
    }
    int count = 0;

    for (int i = 0; i < MAX_ARGS; i++) {
        for (int j = 0; j < MAX_ARG_LENGTH; j++) {
            (*tokenised)[i][j] ='!';
            count += 1;
//            printf("", tokenised[i][j]);
        }
    }
    printf("%d\n", count);

    return tokenised;
}





