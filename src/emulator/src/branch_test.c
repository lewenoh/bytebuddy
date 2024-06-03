#include <stdio.h>
#include <stdbool.h>
#include "branch.h"
#include "testcond.h"
// Jump forward by 2 addresses
// 0001 0100 0000 0000 0000 0000 0000 0010
#define BRANCH_UNCONDITIONAL1 0x14000002
// Jump backward by 2 addresses
// 00010111111111111111111111111110
#define BRANCH_UNCONDITIONAL2  0x17FFFFFE
// R2 = 4 (base10)
// 1101011000011111000000 00010 00000
#define BRANCH_REG1  0xD61F0040
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
// 01010100 11111111111111111000 1011
#define BRANCH_COND3  0x54FFFF8B


void testbranch() {
	struct processor p = {{0x0}, 0x0, {false, true, false, false}, {0x0}};
	branch(&p, BRANCH_UNCONDITIONAL1);
	testcond(p.pc==0x8, "Branch forward by 2");
	
	branch(&p, BRANCH_UNCONDITIONAL2);
	testcond(p.pc==0x0, "Branch backward by 2");

	p.genregs[2] = 0x4;
	branch(&p, BRANCH_REG1);
	testcond(p.pc==0x4, "Branch reg to 0x1");
	
	p.genregs[4] = 0x32;
	branch(&p, BRANCH_REG2);
	testcond(p.pc==0x32, "Branch reg to 0x32");
	
	p.pstate[1] = true;
	branch(&p, BRANCH_COND1);
	testcond(p.pc==0x3E, "Branch EQ forward by 3");

	branch(&p, BRANCH_COND2);
	testcond(p.pc==0x3E, "Branch GT condition fails");

	p.pstate[0] = true;
	branch(&p, BRANCH_COND3);
	testcond(p.pc == 0x2E, "LT holds, backward by 4");
}
	

 
