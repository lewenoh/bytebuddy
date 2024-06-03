#include "dpiReg_test.h"
#include <stdio.h>
#include <stdbool.h>
#include <testcond.h>
#include <dpiReg.h>
#include <processor_def.h>
//Arithmetic 32bit, add lsl, rm=1, shift_amount = 0, rn = 2, rd = 3
// 0 00 0 101 1000 00001 000000 00010 00011
#define TEST1 0xB010043

// Arithmetic 64bit, add set flags,lsl,  rm = 1, shift amount = 60, rn = 2, rd = 3
// 1 01 0 101 1000 00001 111100 00010 00011
#define TEST2 0xAB01F043

// Arithmetic 32b, sub, lsr, rm=10, shiftamount=25, rn=11, rd=13
// 0 10 0 101 1010 01010 011001 01011 01101
#define TEST3 0x4B4A656D

// Arithmetic 64bit, sub set flags, asr, rm=10,sa=25, rn=11, rd=13
// 1 01 0 101 1100 01010 011001 01011 01101
#define TEST4 0xAB8A656D

// Logic 64bit, and, lsl, rm=4, sa=40, rn=5, rd=6
// 1 00 0 101 0000 00100 101000 00101 00110
#define TEST5 0x8A04A0A6

// Logic 32bit bic, lsr, rm=7, sa=15, rn=8 rd=9
// 1 00 0 101 0011 00111 001111 01000 01001
#define TEST6 0x8A673D09

// Logic 64bit orr, asr, rm=4, sa=40, rn=5, rd=6
// 1 01 0 101 0100 00100 101000 00101 00110
#define TEST7 0xAA84A0A6

// Logic 32bit orn, ror, rm=7, sa=15, rn=8, rd=9
// 1 01 0 101 0111 00111 001111 01000 01001
#define TEST8 0xAAE73D09

// Logic 64bit, eor, lsl, rm=4, sa=40, rn=5, rd=6
// 1 10 0 101 0000 00100 101000 00101 00110
#define TEST9 0xCA04A0A6

// Logic 32bit, eon, lsr, rm=7, sa=15, rn=8, rd=9
// 1 10 0 101 0011 00111 001111 01000 01001
#define TEST10 0xCA673D09 

// Logic 64bit ands, asr, rm=4, sa=40, rn=5, rd=6
// 1 11 0 101 0100 00100 101000 00101 00110
#define TEST11 0xEA84A0A6

// Logic 32bit, bics, ror, rm=7, sa=15, rn=8, rd=9
// 1 11 0 101 0111 00111 001111 01000 01001
#define TEST12 0xEAE73D09

void dpiReg_test() {
	struct processor p = {{0x0}, 0x0, {false, true, false, false}, {0x0}};
	p.genregs[1] = 0x1;
	p.genregs[2] = 0x2;
	dpireg(&p, TEST1);
	testcond(p.genregs[3]==0x3, "Arithmetic 32bit, add lsl, rm=1, shift_amount = 0, rn = 2, rd = 3\n");	
	dpireg(&p, TEST2);
	testcond(p.genregs[3]==0x2000002, "Arithmetic 64bit, add set flags,lsl,  rm = 1, shift amount = 60, rn = 2, rd = 3");
	
	p.genregs[10] = 0x4000000;
	p.genregs[11] = 0x1;
	dpireg(&p, TEST3);
	testcond(p.genregs[13]==0x1,"Arithmetic 32b, sub, lsr, rm=10, shiftamount=25, rn=11, rd=13");

	dpireg(&p,TEST4);
	testcond(p.genregs[13]==0x7FFFFFD, "Arithmetic 64bit, sub set flags, asr, rm=10,sa=25, rn=11, rd=13");
	
	p.genregs[4]=0x4;
	p.genregs[5]=0x400000000;
	dpireg(&p,TEST5);
	testcond(p.genregs[6]==0x400000000, "Logic 64bit, and, lsl, rm=4, sa=40, rn=5, rd=6");
	
	p.genregs[7]=0x10000;
	p.genregs[8]=0xFFFFFFFD;
	dpireg(&p,TEST6);
	testcond(p.genregs[9] ==0xFFFFFFFD, "Logic 32bit bic, lsr, rm=7, sa=15, rn=8 rd=9");

	p.genregs[4]=0x400000000;
	p.genregs[5]=0x2;
	dpireg(&p,TEST7);
	testcond(p.genregs[6]==0x2, "Logic 64bit orr, asr, rm=4, sa=40, rn=5, rd=6");

	dpireg(&p,TEST8);
	testcond(p.genregs[9]==0xFFFFFFFD, "Logic 32bit orn, ror, rm=7, sa=15, rn=8, rd=9");

	p.genregs[4]=0x2;
	p.genregs[5]=0x400000000;
	dpireg(&p,TEST9);
	testcond(p.genregs[6]==0x400000000, "Logic 64bit, eor, lsl, rm=4, sa=40, rn=5, rd=6");

}	
