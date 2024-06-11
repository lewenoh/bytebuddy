#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/tokenise.h"
#include "../include/table_def.h"

int main(int argc, char **argv) {

    instruction test_man = "and x0, x0, x0";
    printf("This is the test: %s\n", test_man);

    token_arr *tokenArr;
    tokenArr = tokenise_instruction(test_man);

  // .s file read -> Instruction table, Symbol Table
  // For each instruction, classify.
  // Encode each instruction into binary.
  // Write binary to .bin file.
//  char * test_man = "and x0, x0, x0";
//  token_arr tokenised_test;
//  memcpy(tokenised_test, tokenise_instruction(test_man), sizeof(token_arr));
//  for (int i = 0; i < 4; i++) {
//      printf("Element %d: %s\n", i, tokenised_test[i]);
//  }




  return EXIT_SUCCESS;
}
