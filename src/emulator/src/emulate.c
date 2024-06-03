#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "processor_def.h"
#include "binary_load.h"
#include "binary_output.h"
#include "binary_load_test.h"
#include "binary_output_test.h"
#define ZEROREG 0x0
#define HALTINSTRUCTION 2315255808

int main(int argc, char **argv) { 
  //populating the processor, p
//  struct processor p = {{0x0}, 0x0, {false, true, false, false}, {0x0}};
//  uint32_t ir = p.memory[p.pc/4];
//  //get instruction lines from bin file
//  FILE *inputFile = fopen(argv[1], "rb");
//
//  if (inputFile == NULL || ferror(inputFile)) {
//  	fprintf(stderr, "Error opening input file.\n");
//	exit(1);
// } else {
//  	binary_load(&p, inputFile); // delegates loading to binary_load
// }

//  fclose(inputFile);
//
//
//  //emulator loop:
//  while (ir != HALTINSTRUCTION){
//        //fetch:
//      ir = p.memory[p.pc/4];
//      p.pc += 4; // should this not be at the end of the loop? 
//        //decode and execute: TODO
//
//	i_type instrType = decode(ir);
//
//	switch (instrType) {
//
//	case DPIMM:
//		dpiImm(&p, ir);
//		break;
//
//	case DPREG:
//		dpiReg(&p, ir);
//		break;
//
//	case SDT:
//		sdt(&p, ir);
//		break;
//
//	case LL:
//		ll(&p, ir);
//		break;
//
//	case BRANCH:
//		branch(&p, ir);
//		break; 
//
//	default:
//            fprintf(stderr, "No matching instruction type.\n");
//
//	}

//	p.pc += 4 (?) TODO

//  }
//  //format output
//
//  FILE *outputFile = stdout;
//
//  if (argc == 3) { // if output file is provided
//  	outputFile = fopen(argv[2], "wb");
//  }
//
//  if (outputFile == NULL || ferror(outputFile)) {
//  	fprintf(stderr, "Error writing to output file.\n");
//  	exit(1);
//  } else {
//  	binary_output(&p, outputFile); // delegates to binary_output
//  }

//  if (outputFile != stdout) {
//  	fclose(outputFile);
//  }

  binary_load_test();
  binary_output_test();

  return EXIT_SUCCESS;
}

