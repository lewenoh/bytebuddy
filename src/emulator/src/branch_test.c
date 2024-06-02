#include <stdio.h>
#include <stdbool.h>
#include "branch.h"
// Jump forward by 2 addresses
// 0001 0100 0000 0000 0000 0000 0000 0010
#define BRANCH_UNCONDITIONAL1 0x14000002
// Jump backward by 2 addresses
// 00010111111111111111111111111111
#define BRANCH_UNCONDITIONAL2  0x17FFFFFF
// R2 = 1 (base10)
// 1101011000011111000000 00001 00000
#define BRANCH_REG1  0xD61F0020
// R4 = 50 (10)
// 1101011000011111000000 00100 00000
#define BRANCH_REG2  0xD61F0080
// COND: EQ SATISFIED; Jump by 3 instructions forward.
// 01010100 0000000000000000011 0 0000
#define BRANCH_COND1  0x54000060
// COND: GT NOT SATISFIED;
// 01010100 0000000000000000011 0 1100
#define BRANCH_COND2  0x5400006C
// COND: LT SATISFIED; Jump by 4 instructions back.
// 01010100 1111111111111111100 1100
#define BRANCH_COND3  0x2A7FFFCC

void testcond(bool ok, char *testname) {
	printf("T %s: %s\n", testname, ok?"OK":"FAIL");
}

void testbranch() {
	struct processor p = {{0x0}, 0x0, {false, true, false, false}, {0x0}};
	branch(p, BRANCH_UNCONDITIONAL1);
	testcond(p.pc==0x8, "Branch forward by 2");
	printf("pc: %lx\n", p.pc);
	
	branch(p, BRANCH_UNCONDITIONAL2);
	testcond(p.pc==0x0, "Branch backward by 2");
	printf("pc: %lx\n", p.pc);

	p.genregs[2] = 0x1;
	branch(p, BRANCH_REG1);
	testcond(p.pc==0x4, "Branch reg to 0x1");
	printf("pc: %lx\n", p.pc);
	
	p.genregs[4] = 0x32;
	branch(p, BRANCH_REG2);
	testcond(p.pc==0xC8, "Branch reg to 0x32");
	printf("pc: %lx\n", p.pc);
	
	p.pstate[1] = true;
	branch(p, BRANCH_COND1);
	testcond(p.pc==0xD4, "Branch EQ forward by 3");
	printf("pc: %lx\n", p.pc);

	branch(p, BRANCH_COND2);
	testcond(p.pc==0xD4, "Branch GT condition fails");
	printf("pc: %lx\n", p.pc);

	p.pstate[0] = true;
	testcond(p.pc == 0xC4, "LT holds, backward by 4");
	printf("pc: %lx\n", p.pc);
}
	

 
