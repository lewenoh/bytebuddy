#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "processor_def.h"
#include "dpiImm.c"

void testcond( bool ok, char *testname)
{
	printf( "T %s: %s\n", testname, ok?"OK":"FAIL");
}

void init_processor ( struct processor *p) {

	p->genregs[0] = 2;
	p->genregs[1] = 5;
	p->genregs[2] = -4;
	p->genregs[3] = -10; // initialising our sample registers

	for (int i = 4; i < 31, 1 ++) {
		p->genregs[i] = i; // initialising the rest of the registers			
	}    
	p->pc = 0;
	p->pstate = {false, false, false, false};
	memset(p->memory, 0, sizeof(p->memory)); // sets all values of memory to 0 because we do not need memory
}

void test1() {
	dpiImm( 0x11000026, p);
	testcond( p.genregs[6] == 7, "Testing 5 + 2 = 7");
}

void main() {
	test1();
}

// here should create a sample processor and have regs empty except for two
// and do uint_64 addition and test that the answer is correct
// like
// set ir to be the fixed instruction for this type of addition
// set registers to be certain numbers and then test it.
// testcond ( dpiImm( .. , p) == 1, "addition of 4 and 5 is 9")
