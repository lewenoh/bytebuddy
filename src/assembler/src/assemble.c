#include <stdlib.h>
#include <stdio.h>
#include "dpi_encoder.h"

int main(int argc, char **argv) {
  // .s file read -> Instruction table, Symbol Table
  // For each instruction, classify.
  // Encode each instruction into binary.
  // Write binary to .bin file. 
  char eg[5][30] = {"mneg", "x17", "x1", "x0"};
  printf("%x\n", dpi_encoder(eg));
  return EXIT_SUCCESS;
}
