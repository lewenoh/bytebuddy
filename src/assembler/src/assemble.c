#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "helperfuncs.h"

int main(int argc, char **argv) {
  // .s file read -> Instruction table, Symbol Table
  // For each instruction, classify.
  // Encode each instruction into binary.
  // Write binary to .bin file. 
  	char imm[30];
	strcpy(imm, "0x14");
  	uint32_t ans = readimm(imm);
	printf("%x, %d\n", ans, ans);
	return EXIT_SUCCESS;
}
