//#include "../include/tokenise_instruction.h"
//#include <stdio.h>
//#include <string.h>
//#include <stdbool.h>
//#include <assert.h>
//
//
////  INPUT: tok_instr is the string buffer that will contain the tokenised instruction.
////  INPUT: raw_instr is the string literal of the raw instruction itself.
////  INPUT: symbols is symbol table
//
//// Tokenise raw instr (char*) -> (string[5])
//// Classify the instruction. Tokenise based on classification.
//
//
//int mandatory_args = 0;
//
//int classify_instruction(char *instr_identifier) {
//    if (strcmp(instr_identifier, "cmp") == 0 ||
//        strcmp(instr_identifier, "cmn") == 0 ||
//        strcmp(instr_identifier, "neg") == 0 ||
//        strcmp(instr_identifier, "negs") == 0 ||
//        strcmp (instr_identifier, "tst") == 0 ||
//        strcmp (instr_identifier, "movk") == 0 ||
//        strcmp (instr_identifier, "movn") == 0 ||
//        strcmp (instr_identifier, "movz") == 0 ||
//        strcmp (instr_identifier, "mov") == 0 ||
//        strcmp (instr_identifier, "mvn") == 0
//        ) {
//        return 2;
//    } else if (
//            strcmp(instr_identifier, "madd") == 0 ||
//            strcmp(instr_identifier, "msub") == 0
//    ) {
//        return 4;
//    } else {
//        return 3;
//    }
//}
//
//
//char* tokenise_mandatory_args(token_arr *tokenised_, instruction raw_instr) {
//    // Initialise tokednised array. Default is '\0' char.
//    memset(tokenised, '\0', sizeof(*tokenised));
//
//    // split by ", "
//    // For first token use to classify instruction i_type.
//    // Once classified read rest.
//    // Now know the limit for mandatory args.
//    // If there is optional, then split by " " and then put in separately into tokenised.
//
//    char *token;
//    token = strtok(raw_instr, " ");
//
//    // Classify the instruction.
//    // Find number of mandatory args.
//    mandatory_args = classify_instruction(token);
//
//
//    for (int i = 0; i < mandatory_args; i++) {
//        // Pass argument into token.
//        token = strtok(NULL, ", ");
//
//        // Mandatory argument must be present in the raw input instruction.
//        assert(token != NULL);
//
//        // Copy argument into tokenised.
//        strcpy(*tokenised[i], token);
//    }
//    return token;
//}
//
//void tokenise_optional_args(token_arr *tokenised, instruction optional_args, int mand_args) {
//    char *opt_arg;
//    opt_arg = strtok(optional_args, " ");
//    strcpy(*tokenised[mand_args], opt_arg);
//    opt_arg = strtok(NULL, " ");
//    strcpy(*tokenised[mand_args+1], opt_arg);
//}
//
//
//
//// Switch out labels for addresses.
//// Return tokednised array. char arr[5][30]
//token_arr *tokenise_instruction(char* raw_instr) {
//    token_arr *tokenised;
//    // Initialise tokednised array. Default is '\0' char.
//    for (int i = 0; i < 5; i++) {
//        for (int j = 0; j < 30; j++) {
//            strcpy(tokenised[i], "\0");
//        }
//    }
//    memset(tokenised, '\0', sizeof(*tokenised));
//
//    char *rem_instruction;
//    rem_instruction = tokenise_mandatory_args(tokenised, raw_instr);
//
//    rem_instruction = strtok(NULL, ", ");
//    if (rem_instruction != NULL) {
//        // There are optional args in instruction8.
//        tokenise_optional_args(tokenised, rem_instruction, mandatory_args);
//    }
//
//    return tokenised;
//}
//
