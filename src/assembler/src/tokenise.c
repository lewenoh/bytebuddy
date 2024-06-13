//
// Created by js5422 on 11/06/24.
//

#include "../include/tokenise.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

token_arr *initialise_token_arr() {

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
    return tokenised;

}

char* read_word(instruction c, index i, instruction raw_instr, char * buffer) {
    // Calculate index of first white space character
    while (*c != ' ') {
        // Calculate index.
        i++;
        // Increment pointer.
        c++;
    }
    // i points to the first white space character.
//    int length = i;
//    char *buffer = (char*)malloc(sizeof(char)*length);



//    printf("%d\n", i);
    strncpy(buffer, raw_instr, i+1);
    return buffer;

}

void skip_space(instruction *p_instr, int *index) {
    // Delete whitespace
//    printf("Before: %d\n", index);
    while (isspace(**p_instr) || **p_instr==',') {
        (*index)++;
        ((*p_instr)++);
    }
//    printf("%d\n", index);
    // Makes i and c equal to the first non-delimiter character.
}

void process_args(int num_args, instruction c, int *index, instruction raw_instr, token_arr *tokenArr) {
    int i = 1;
    int init_index;
    while (num_args != 0) {
        init_index = *index;
        // Read word
        while (*c != ',' && *c != '\0') {
            // Calculate index.
            (*index)++;
            // Increment pointer.
            c++;
        }
        // i points to the first white space character.
//        int length = index;
        int j = 0;
        for (int start = init_index; start < *index; start ++) {
            (*tokenArr)[i][j] = raw_instr[start];
            j++;

        }
        skip_space(&c, index);

        num_args --;
        i ++;
    }
    return;
}

    token_arr *tokenise(char *raw_instr) {

        token_arr *tokenised;
        tokenised = initialise_token_arr();

        // classify and set mand_args.
        // Assume no whitespace at beginning
        // Loop through the string and store until hit whitespace or comma.
        // Store this index. strncopy into buffer by that size.
        // Iterate through the rest and delete the first n bytes.
        // Loop through until hit no whitespace or comma.

        int i = 0;
        char *c = raw_instr;

        while (*c != ' ') {
            // Calculate index.
            i++;
            // Increment pointer.
            c++;
        }
        // i points to the first white space character.
        // Buffer is needed for classification.
        char *buffer = malloc(sizeof(char)*(i+1));
        if (buffer == NULL) {
            abort();
        }
        strncpy(buffer, raw_instr, i);
        buffer[i] = '\0';
        printf("Comp Result: %d\n", strcmp(buffer, "madd"));
        strncpy(*tokenised[0], raw_instr, i);
        skip_space(&c, &i);

        int mand_args;
        if (strcmp(buffer, "cmp") == 0 ||
            strcmp(buffer, "cmn") == 0 ||
            strcmp(buffer, "neg") == 0 ||
            strcmp(buffer, "negs") == 0 ||
            strcmp(buffer, "tst") == 0 ||
            strcmp(buffer, "movk") == 0 ||
            strcmp(buffer, "movn") == 0 ||
            strcmp(buffer, "movz") == 0 ||
            strcmp(buffer, "mov") == 0 ||
            strcmp(buffer, "mvn") == 0) {
            // Mand_args 2 case.
            mand_args = 2;
            process_args(mand_args, c, &i,raw_instr, tokenised);


        } else if (
                strcmp(buffer, "madd") == 0 ||
                strcmp(buffer, "msub") == 0
                ) {
            mand_args = 4;
            printf("I got here\n");
            process_args(mand_args, c, &i,raw_instr, tokenised);

        } else if (
                strcmp(buffer, ".int") == 0
                ) {
            mand_args = 1;
            process_args(mand_args, c, &i,raw_instr, tokenised);
        } else if (strcmp(buffer, "b.cond") == 0 ||
                   strcmp(buffer, "br") == 0) {
            mand_args = 1;
        } else if (strcmp(buffer, "ldr") == 0 ||
        strcmp(buffer, "str")==0){
            // str, ldr case
            mand_args = 2;
        } else {
            // 3 arg case.
            mand_args = 3;
            process_args(mand_args, c, &i,raw_instr, tokenised);

        }

        free(buffer);
        return tokenised;


    }


