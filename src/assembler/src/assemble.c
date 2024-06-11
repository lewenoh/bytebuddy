#include <stdlib.h>
#include <stdio.h>
#include "branch_encoder.h"

int main(int argc, char **argv) {
  // .s file read -> Instruction table, Symbol Table
  // For each instruction, classify.
  // Encode each instruction into binary.
  // Write binary to .bin file. 
  char eg[6][30] = {"b", "#0x8", "\0", "\0", "\0", "\0"};
  printf("%x\n", branch_encoder(0x0, eg));
	return EXIT_SUCCESS;
}
