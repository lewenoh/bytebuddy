#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <custom_tests.h>
#include "processor_def.h"
#include "binary_load.h"
#include "binary_output.h"
#include "dpiReg.h"
#include "sdt.h"
#include "ll.h"
#include "dpiImm.h"
#include "branch.h"
#include "decoder.h"
#define ZEROREG 0x0
#define HALTINSTRUCTION 0x8a000000
#define CELL_SIZE 4
#define BYTE 0xff
#define BYTE_SIZE 8
#define BYTES 8

int main(int argc, char **argv) {
	//run_custom_tests();
	//populating the processor, p
	struct processor p = {{0x0}, 0x0, {false, true, false, false}, {0x0}};
	uint32_t ir = p.memory[p.pc/CELL_SIZE];

	//get instruction lines from bin file
	FILE *inputFile = fopen(argv[1], "rb");

	if (inputFile == NULL || ferror(inputFile)) {
	fprintf(stderr, "Error opening input file.\n");
	exit(1);
	} else {
	binary_load(&p, inputFile); // delegates loading to binary_load
	}

	fclose(inputFile);
	
	unsigned int remainder;
	//emulator loop:
	while (ir != HALTINSTRUCTION){
	//fetch:
	p.pc += BYTES-1;
	for (int x = 0; x < BYTES; x++){
		remainder = p.pc % CELL_SIZE;
		ir = (ir << BYTE_SIZE) + ((p.memory[p.pc/CELL_SIZE] >> (remainder * BYTE_SIZE)) & BYTE);
		p.pc --;
	}
	p.pc ++;
	
	
	//decode and execute:
	i_type instrType = decode(ir);

	switch (instrType) {

		case DPIMM:
			dpiImm(&p, ir);
			break;

		case DPREG:
			dpireg(&p, ir);
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
		p.pc += CELL_SIZE;

	}
	p.pc -= CELL_SIZE;
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

