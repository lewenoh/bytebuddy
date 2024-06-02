#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "processor_def.h"
#include "dpiImm.h"
#include "dpiImm_add_test.h"
#include "testcond.h"
#include <inttypes.h> // for PRIu64

void init_processor ( struct processor *p) {

	p->genregs[0] = 2;
	p->genregs[1] = 5;
	p->genregs[2] = (uint64_t)-4;
	p->genregs[3] = (uint64_t)-10; // initialising our sample registers
	p->genregs[31] = 0xffffffffffffffff; // have a max value register

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

// add test:
void test1(struct processor *p) {
    dpiImm(p, 0x11000826);
    char test_result[50]; // Buffer to hold the formatted string
    snprintf(test_result, sizeof(test_result), "Testing 2 + R1[5], expecting: 7 , got: %" PRIu64, p->genregs[6]);
    testcond(p->genregs[6] == 7, test_result);
}

// adds tests:
// N flag test:
void test2(struct processor *p) {
	dpiImm(p, 0x31000447);
	char test_result[50];
	snprintf(test_result, sizeof(test_result), "Testing 1 + R[2](-4), expecting: -3, got: %" PRIu64, p->genregs[7]);
	testcond((p->genregs[7] == -3 && p->pstate[0] == 1), test_result);
}

// Z flag test:
void test3(struct processor *p) {
	dpiImm(p, 0x31001048);
	char test_result[100];
        snprintf(test_result, sizeof(test_result), "Testing 4 + R[2](-4), expecting: 0, 0, 1, 0, 0 got: %" PRIu64 ", %d, %d, %d, %d", p->genregs[8], p->pstate[0], p->pstate[1], p->pstate[2], p->pstate[3]);
        testcond((p->genregs[8] == 0 && p->pstate[0] == 0  && p->pstate[1] == 1 && p->pstate[2] == 0 && p->pstate[3] == 0), test_result);

}

// C flag test:
void c_flag_test1(struct processor *p) {
	dpiImm(p, 0x310013E9);
	char test_result[100];
        snprintf(test_result, sizeof(test_result), 
			"Testing 4 + R[31](max), expecting: 3, 0, 0, 1, 0 got: %" PRIu64 ", %d, %d, %d, %d", 
			p->genregs[9], p->pstate[0], p->pstate[1], p->pstate[2], p->pstate[3]);
        testcond((p->genregs[9] == 3 && p->pstate[0] == 0  && p->pstate[1] == 0 && p->pstate[2] == 1 && p->pstate[3] == 0), test_result);
}


void dpiImm_add_tests() {
	struct processor p;
	init_processor(&p);
	test1(&p);
	test2(&p);
	test3(&p);
	c_flag_test1(&p);
}

