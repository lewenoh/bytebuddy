#include "ll_test.h"
#include "testcond.h"
// 32-bit ll, simm19 = 15 (10), rt = 1
//0 0 011000 0000000000000001111 00001
#define LL1 0x180001E1

// 64-bit ll, simm19 = -10 (10), rt = 4
//0 1 011000 1111111111111110110 00100
#define LL2 0x58FFFEC4
#define MEMORY_VALUE 0xAAA

void test_ll() {
	struct processor p =  {{0x0}, 0x0, {false, true, false, false}, {0x0}};
	// 32bit
	// set pc to 4
	p.pc = 0x15;
	// Mem[0x40] = MEMORY_VALUE
	p.memory[0x40] = MEMORY_VALUE;
	
	// load from address 4 + 15 * 4 = 64 = 0x40
	// load to register 1
	//run test
	ll(&p, LL1);
	testcond(p.genregs[1] == 0x5, "32 bit shift");



