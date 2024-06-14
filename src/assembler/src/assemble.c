#include <stdlib.h>
#include <stdio.h>
#include "sdt_encoder.h"

int main(int argc, char **argv) {
  // .s file read -> Instruction table, Symbol Table
  // For each instruction, classify.
  // Encode each instruction into binary.
  // Write binary to .bin file. 
  char eg[6][30] = {"str", "x1", "x2", "x4", "\0", "N"};
  printf("%x\n", sdt_encoder(0xc, eg));
	return EXIT_SUCCESS;
}
