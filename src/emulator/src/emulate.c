#include <stdlib.h>	
#include <stdbool.h>
#include <stdio.h>
#include "processor_def.h"
#include "binary_load.h"
#define ZEROREG 0x0
#define HALTINSTRUCTION 2315255808

int main(int argc, char **argv) { 
  //populating the processor, p
  struct processor p = {{0x0}, 0x0, {false, true, false, false}, {0x0}};
  uint32_t ir = p.memory[p.pc/4];
  //get instruction lines from bin file
  FILE *inputFile = fopen(argv[1], "rb");
  
  if (inputFile == NULL) {
  	fprintf(stderr, "Error opening input file.\n");
	exit(1);
 }

  FILE *outputFile = stdout;

  if (argc == 3) { // if output file is provided
  	outputFile = fopen(argv[2], "wb");
  }

  if (outputFile == NULL) {
	fprintf(stderr, "Error writing to output file.\n");
	exit(1);
  }

  binary_loader(p, inputFile, outputFile); // delegates loading to binary_loader

  fclose(inputFile);
  
  if (outputFile != stdout) {
	fclose(outputFile);
  }

  //emulator loop:
  while (ir != HALTINSTRUCTION){
        //fetch:
      ir = p.memory[p.pc/4];
      p.pc += 4;
        //decode and execute: TODO
  }
  //format output TODO
  return EXIT_SUCCESS;
}
