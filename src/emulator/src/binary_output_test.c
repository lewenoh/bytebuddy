#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "binary_output.h"
#include "processor_def.h"


void binary_output_test() {

	struct processor p = {{0x0}, 0x0, {false, true, false, false}, {0x0}}; // initialise processor

        FILE *outputFile = stdout;

	for (int i = 0; i < 31; i++) {
		p.genregs[i] = i;
	}

	p.pc = 0x4;

	p.memory[0] = 1;
	p.memory[1] = 2;
	p.memory[2] = 3;
	p.memory[7] = 4;
	p.memory[4] = 5;
	p.memory[5] = 6;

	binary_output(&p, outputFile);

}
