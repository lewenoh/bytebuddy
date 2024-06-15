//
// Created by js5422 on 11/06/24.
//

#include "../include/tokenise.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

token_arr *initialise_token_arr() {

    // Initialise tokenised array. Default is '\0' char.
    token_arr *tokenised = malloc(sizeof(token_arr));
    if (tokenised == NULL) {
        free(tokenised);
        abort();
    }

    for (int i = 0; i < MAX_ARGS; i++) {
        for (int j = 0; j < MAX_ARG_LENGTH; j++) {
            (*tokenised)[i][j] =NULL_CHAR;
        }
    }
    return tokenised;
}

void skip_space(instruction *p_instr, int *index) {
    // Makes i and c equal to the first non-delimiter character.
    while (isspace(**p_instr) || **p_instr==',') {
        (*index)++;
        ((*p_instr)++);
    }

}

void slice_string(int start, int end, int string_no, instruction raw_instr, token_arr *tokenArr) {
    // Slices the string from the start by (end-start) times
    int i = 0;
    for (; start < end; start ++) {
        (*tokenArr)[string_no][i] = raw_instr[start];
        i++;
    }
}


bool process_args(int num_args, instruction *pc, int *index, char delim,
                  instruction raw_instr, token_arr *tokenArr, int arg_index) {
    // Gets num_args number of args into c.
    // Skips white space at the end.
    bool optional_args = false;
    int i = arg_index;
    int init_index;
    while (num_args != 0) {
        init_index = *index;
        // Read word
        while (**pc != delim && **pc != '\0') {
            // Calculate index.
            (*index)++;
            // Increment pointer.
            (*pc)++;
        }
        // i points to the first white space character.
        slice_string(init_index, *index, i, raw_instr, tokenArr);
        if (num_args == 1 && **pc == ',') {
            optional_args = true;
        }

        skip_space(pc, index);
        num_args --;
        i ++;
    }
    return optional_args;
}

void process_memory_addressing(instruction *pc, int *index, instruction raw_instr, token_arr *tokenArr) {
    (*pc)++;
    (*index)++;
    int i = 2;
    int init_index = *index;
    int num_parsed = 0;
    bool contains_hash = false;
    while (**pc != ']') {
        // Calculate index.
        // Checks for hash.
        if (**pc == '#') {
            contains_hash = true;
        }
        if (**pc == ',') {
            // Read into arr, skip space, and increment number of args parsed.
            slice_string(init_index, *index, i, raw_instr, tokenArr);
            skip_space(pc, index);
            init_index = *index;
            i++;
            num_parsed++;
        } else {
            (*index)++;
            (*pc)++;
        }
    }
    // Read last argument before ].
    slice_string(init_index, *index, i, raw_instr, tokenArr);
    skip_space(pc, index);
    num_parsed++;

    // Calculate index.
    (*index)++;
    // Increment pointer.
    (*pc)++;

    int last_index = MAX_ARGS -1;
    if (num_parsed == 2 && contains_hash && (**pc == '\0')) {
        // U
        strcpy((*tokenArr)[last_index], "U");
    } else if (num_parsed == 2 && contains_hash) {
        // Pre
        strcpy((*tokenArr)[last_index], "PRE");
    } else if (num_parsed == 1) {
        // Post
        strcpy((*tokenArr)[last_index], "POST");
        i++;

        skip_space(pc, index);
        init_index = *index;
        // Read word
        while (**pc != '\0') {
            // Calculate index.
            (*index)++;
            // Increment pointer.
            (*pc)++;
        }
        // i points to the first white space character.
        slice_string(init_index, *index, i, raw_instr, tokenArr);
    } else {
        // None of the above.
        strcpy((*tokenArr)[last_index], "N");
    }
}

void process_branch_args(instruction *pc, int *index, instruction raw_instr, token_arr *tokenArr,
                         symbol_table symbolTable) {
    int init_index;
    init_index = *index;
    // Read word
    while (**pc != '\0') {
        // Calculate index.
        (*index)++;
        // Increment pointer.
        (*pc)++;
    }
    // i points to the first white space character.
    int buffer_length = *index-init_index+1;
    char * buffer = (char *)malloc(sizeof(char)*buffer_length);
    int i = 0;
    int start = init_index;
    bool first_char = false;
    bool second_char = false;
    for (; start < *index; start ++) {
        buffer[i] = raw_instr[start];
        if (i == 0 && buffer[i] == '0') {
            first_char = true;
        }
        if (i==1 && buffer[i] == 'x') {
            second_char = true;
        }
        i++;
    }

    if (first_char && second_char) {
        // Normal address
        slice_string(init_index, *index, 1, raw_instr, tokenArr);
    } else {
        address a;
        a = get_address(symbolTable, buffer);
        assert(a!=NULL);
        strcpy((*tokenArr)[1], a);
    }
    free(buffer);
}

token_arr *tokenise(char *raw_instr, symbol_table *symbolTable) {

        token_arr *tokenised;
        tokenised = initialise_token_arr();

        int i = 0;
        char *c = raw_instr;
        // // Find index after instruction identifer.
        while (!isspace(*c)) {
            i++;
            c++;
        }

        // Buffer is needed for classification.
        char *buffer = malloc(sizeof(char)*(i+1));
        if (buffer == NULL) {
            abort();
        }
        strncpy(buffer, raw_instr, i);
        buffer[i] = '\0';
        strncpy(*tokenised[0], raw_instr, i);
        skip_space(&c, &i);

        // classify and set mand_args.
        // Assume no whitespace at beginning
        int mand_args;
        bool optional_args;
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
            optional_args = process_args(mand_args, &c, &i, ',',
                         raw_instr, tokenised, 1);

            if (optional_args) {
                // Optional Parameters exist
                process_args(2, &c, &i, ' ', raw_instr, tokenised, 3);
            }
        } else if (
                strcmp(buffer, "madd") == 0 ||
                strcmp(buffer, "msub") == 0
                ) {
            mand_args = 4;
            process_args(mand_args, &c, &i, ',',
                         raw_instr, tokenised, 1);
        } else if (
                strcmp(buffer, ".int") == 0 ||
                strcmp(buffer, "br") == 0
                ) {
            mand_args = 1;
            process_args(mand_args, &c, &i, ',',
                         raw_instr, tokenised, 1);
        } else if (strcmp(buffer, "b") == 0 ||
                   strcmp(buffer, "b.eq") == 0 ||
                strcmp(buffer, "b.ne") == 0 ||
                strcmp(buffer, "b.ge") == 0 ||
                strcmp(buffer, "b.lt") == 0 ||
                strcmp(buffer, "b.gt") == 0 ||
                strcmp(buffer, "b.le") == 0 ||
                strcmp(buffer, "b.al") == 0){
            process_branch_args(&c, &i, raw_instr, tokenised, *symbolTable);

        }
        else if (strcmp(buffer, "ldr") == 0 ||
        strcmp(buffer, "str")==0){
            // str, ldr case
            mand_args = 1;
            // Take the first argument.
            process_args(mand_args, &c, &i, ',',
                         raw_instr, tokenised, 1);
            if (*c != '[') {
                // ldr <Rt> <literal>
                process_args(mand_args, &c, &i, ',',
                             raw_instr, tokenised, 2);
            } else {
                process_memory_addressing(&c, &i, raw_instr, tokenised);
            }
        } else {
            // 3 arg case.
            mand_args = 3;
            optional_args = process_args(mand_args, &c, &i, ',',
                                         raw_instr, tokenised, 1);

            if (optional_args) {
                // Optional Parameters exist
                process_args(2, &c, &i, ' ', raw_instr, tokenised, 4);
            }

        }

        free(buffer);
        return tokenised;
    }






