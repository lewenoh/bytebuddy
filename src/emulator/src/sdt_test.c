#include "sdt_test.h"
#include "testcond.h"
//load reg offset, 32 bit, xm = reg3, xn = reg7, rt = reg8
//1011 1000 0110 0011 0110 1000 1110 1000
#define LREGOFFSET32 0xb86368e8

//load reg offset, 64 bit, same as LREGOFFSET32, but first 4 bits = F
#define LREGOFFSET64 0xf86368e8

//store reg offset, 32 bit, xm = reg1, xn = reg12, rt = reg8
//1011 1000 0010 0001 0110 1001 1000 1000
#define SREGOFFSET32 0xb8216988

//store reg offset, 64 bit, same as SREGOFFSET32, but first 4 bits = F
#define SREGOFFSET64 0xf8216988

//load/store works for 32/64, and as it is seperate to getting the address, i only need to test the right address for pre/post, no need to test load/store or 32/64

//load pre index, 32 bit, positive simm9 = 20, xn = 4, rt = 9
//1011 1000 0100 0001 0100 1100 1000 1001
#define LPRE32POS 0xb8414c89

//load post index, 32 bit, same as LPRE32POS but 6th 4 bits are 0100
#define LPOST32POS 0xb8414489

//load pre index, 32 bit, negative simm9 = -8, xn = 4, rt = 9
//1011 1000 0101 1111 1000 1100 1000 1001
#define LPRE32NEG 0xb85f8c89

//load unsigned offset, 32 bit, imm12 = 7, xn = 4, rt = 9
//1011 1001 0100 0000 0001 1100 1000 1001
#define LUO32 0xb9401c89

//load unsigned offset, 64 bit, same as LUO32, but first 4 bits is F
#define LUO64 0xf9401c89

void test_sdt() {
	struct processor p = {{0x0}, 0x0, {false, true, false, false}, {0x0}};
	
	//lregoffset32
	p.genregs[3] = 0x20;
	p.genregs[7] = 0x14;
	//retrieved from address 32 + 20 = 52
	p.memory[52/4] = 0x12000000;
	p.genregs[8] = 0x10000000ffffffff;
	sdt(&p, LREGOFFSET32);
	testcond(p.genregs[8] == 0x1000000012000000, "sdt, 32 bit reg offset load");
	
	//lregoffset64
	p.memory[14] = 0x34000000;
	sdt(&p, LREGOFFSET64);
	testcond(p.genregs[8] == 0x3400000012000000, "sdt, 64 bit reg offset load");

	//sregoffset32
	p.genregs[1] = 0x14;
	p.genregs[12] = 0x20;
	p.genregs[8] = 0xffffffff80000008;
	sdt(&p, SREGOFFSET32);
	testcond(p.memory[13] == 0x80000008, "sdt, 32 bit reg offset store");

	//sregoffset64
	sdt(&p, SREGOFFSET64);
	testcond(((p.memory[13] == 0x80000008) && (p.memory[14] == 0xffffffff)), "sdt, 64 bit reg offset store");	

	//lpre32pos
	p.genregs[4] = 0x4;
	//retrieved from address 4 + 20 = 24
	p.memory[24/4] = 0x70000007;
	sdt(&p, LPRE32POS);
	testcond(((p.genregs[9] == 0x70000007) && (p.genregs[4] == 0x18)), "sdt, 32 bit pre index, positive simm load");

	//lpost32pos
	p.genregs[4] = 0x4;
	//retrieved from address 4
	p.memory[4/4] = 0xa000000a;
	sdt(&p, LPOST32POS);
	testcond(((p.genregs[9] == 0xa000000a) && (p.genregs[4] ==0x18)), "sdt, 32 bit post index, positive simm load");

	//lpre32neg
	//address is 24 - 8 = 16
	p.memory[16/4] = 0xb000000b;
	sdt(&p, LPRE32NEG);
	testcond(((p.genregs[9] == 0xb000000b) && (p.genregs[4] == 0x10)), "sdt, 32 bit pre index, negative simm load");

	//luo32
	//address is 16 + 7*4 = 44
	p.memory[44/4] = 0xc000000c;
	sdt(&p, LUO32);
	testcond(p.genregs[9] == 0xc000000c, "sdt 32 bit unsigned offset");

	//lluo64
	//address is 16 + 7 * 8 = 72
	p.memory[72/4] = 0xd000000d;
	p.memory[19] = 0xe000000e;
	sdt(&p, LUO64);
	testcond(p.genregs[9] == 0xe000000ed000000d, "sdt 64 bit unsigned offset");
}
