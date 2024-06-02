#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "processor_def.h"
#include "dpiImm.h"
#include "dpiImm_add_test.h"
#include "testcond.h"

void init_processor ( struct processor *p) {

	p->genregs[0] = 2;
	p->genregs[1] = 5;
	p->genregs[2] = -4;
	p->genregs[3] = -10; // initialising our sample registers

	for (int i = 4; i < 31; i++) {
		p->genregs[i] = i; // initialising the rest of the registers			
	}    
	p->pc = 0;
	p->pstate[0] = false;
	p->pstate[1] = false;
	p->pstate[2] = false;
	p->pstate[3] = false;

	memset(p->memory, 0, sizeof(p->memory)); // sets all values of memory to 0 because we do not need memory
}

void test1(struct processor *p) {
    dpiImm(p, 0x11000826);
    char test_result[50]; // Buffer to hold the formatted string
    snprintf(test_result, sizeof(test_result), "Testing 5 + 2 = 7, got:%llu", p->genregs[6]);
    testcond(p->genregs[6] == 7, test_result);
}

void dpiImm_add_tests() {
	struct processor p;
	init_processor(&p);
	test1(&p);
}

// here should create a sample processor and have regs empty except for two
// and do uint_64 addition and test that the answer is correct
// like
// set ir to be the fixed instruction for this type of addition
// set registers to be certain numbers and then test it.
// testcond ( dpiImm( .. , p) == 1, "addition of 4 and 5 is 9")
