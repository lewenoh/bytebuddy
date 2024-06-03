#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "processor_def.h"
<<<<<<< HEAD
#include "branch_test.h"
=======
#include "binary_load.h"
#include "binary_output.h"
#include "binary_load_test.h"
#include "binary_output_test.h"
>>>>>>> binary_file_loader
#define ZEROREG 0x0
#define HALTINSTRUCTION 2315255808
#include "dpiReg_test.h"

int main(int argc, char **argv) { 
  //populating the processor, p
  //get instruction lines from bin file TODO
  struct processor p = {{0x0}, 0x0, {false, true, false, false}, {0x0}};
  uint32_t ir = p.memory[p.pc/4];
  //get instruction lines from bin file
  FILE *inputFile = fopen(argv[1], "rb");

  if (inputFile == NULL || ferror(inputFile)) {
  	fprintf(stderr, "Error opening input file.\n");
	exit(1);
 } else {
  	binary_load(&p, inputFile); // delegates loading to binary_load
 }

  fclose(inputFile);

  //emulator loop:
  //while (ir != HALTINSTRUCTION){
        //fetch:
      //ir = p.memory[p.pc/4];
      //p.pc += 4;
        //decode and execute: TODO
  //}
  //format output TODO
      ir = p.memory[p.pc/4];
        //decode and execute:

	i_type instrType = decode(ir);

	switch (instrType) {

	case DPIMM:
		dpiImm(&p, ir);
		break;

	case DPREG:
		dpiReg(&p, ir);
		break;

	case SDT:
		sdt(&p, ir);
		break;

	case LL:
		ll(&p, ir);
		break;

	case BRANCH:
		branch(&p, ir);
		break;

	default:
            fprintf(stderr, "No matching instruction type.\n");

	}

	p.pc += 4;

  }
  //format output

  FILE *outputFile = stdout;

  if (argc == 3) { // if output file is provided
  	outputFile = fopen(argv[2], "wb");
  }

  if (outputFile == NULL || ferror(outputFile)) {
  	fprintf(stderr, "Error writing to output file.\n");
  	exit(1);
  } else {
  	binary_output(&p, outputFile); // delegates to binary_output
  }

  if (outputFile != stdout) {
  	fclose(outputFile);
  }
  return EXIT_SUCCESS;
}

