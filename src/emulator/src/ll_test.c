#include "ll_test.h"
#include "testcond.h"
// 32-bit ll, simm19 = 15 (10), rt = 1
//0 0 011000 0000000000000001111 00001
#define LL1 0x180001E1

// 32-bit ll, simm19 = -10 (10), rt = 4
//0 0 011000 1111111111111110110 00100
#define LL2 0x18FFFEC4

//64 bit ll, simm19 = 7, rt = 1
//same as ll1, but first 4 bits are 0101
#define LL3 0x580000E1

//64 bit ll, simm19 = -3, rt = 16
//0101 1000 1111111111111111101 10000
#define LL4 0x58FFFFB0

void test_ll() {
	struct processor p = {{0x0}, 0x0, {false, true, false, false}, {0x0}};	
	//ll1 - store value in 60 
	p.memory[60/4] = 0x10000001; //memory[15]
	p.genregs[1] = 0x20000002ffffffff;
	ll(&p, LL1);
	testcond(p.genregs[1] == 0x2000000210000001, "ll, 32 bit reg, positive simm19");

	//ll2 - store value in 60
	//address = pc - (4*10), pc = 100
	p.pc = 0x64;
	ll(&p, LL2);
	testcond(p.genregs[4] == 0x10000001, "ll, 32 bit reg, negative simm19");

	//ll3 - value from 0x80 (128) and 0x84
	p.memory[128/4] = 0x30000003;
	p.memory[33] = 0x40000004;
	ll(&p, LL3);
	testcond(p.genregs[1] == 0x4000000430000003, "ll, 64 bit reg, positive simm19");

	//ll4, - value from 0x58 (88) and 0x62
	p.memory[88/4] = 0x50000005;
	p.memory[23] = 0x60000006;
	ll(&p, LL4);
	testcond(p.genregs[16] == 0x6000000650000005, "ll, 64 bit reg, negative simm19");
}
