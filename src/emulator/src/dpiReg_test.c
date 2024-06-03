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

// Arithmetic 32b, sub set flags, asr, rm=10,sa=0, rn=11, rd=13
// 0 11  0 101 1100 01010 000000 01011 01101
#define SUBS_NO_SHIFT 0x6BCA016D

// Logic 64bit, and, lsl, rm=4, sa=40, rn=5, rd=6
// 1 00 0 101 0000 00100 101000 00101 00110
#define TEST5 0x8A04A0A6

// Logic 32bit bic, lsr, rm7,sa0,rn8,rd9
// 1 00 0 101 0011 00111 000000 01000 01001
#define BIC_NO_SHIFT 0x8A670109

// Logic 32bit bic, lsr, rm=7, sa=15, rn=8 rd=9
// 1 00 0 101 0011 00111 001111 01000 01001
#define BIC_SHIFT 0x8A673D09

// Logic 64, orr, asr, rm4,sa=0,rn=5,rd=6
// 1 01 0 101 0100 00100 000000 00101 00110
#define ORR_NO_SHIFT 0xAA8400A6

// Logic 64bit orr, asr, rm=4, sa=40, rn=5, rd=6
// 1 01 0 101 0100 00100 101000 00101 00110
#define TEST7 0xAA84A0A6

// Logic 32 bit orn, ror, rm7, sa0, rn8, rd9
// 0  01 0 101 0111 00111 000000 01000 01001
#define ORN_NO_SHIFT 0x2AE70109

// Logic 32bit orn, ror, rm=7, sa=15, rn=8, rd=9
// 0 01 0 101 0111 00111 001111 01000 01001
#define TEST8 0x2AE73D09

// Logic 64bit, eor, lsl, rm=4, sa=40, rn=5, rd=6
// 1 10 0 101 0000 00100 101000 00101 00110
#define TEST9 0xCA04A0A6

// Logic 64 bit, eor, lsl, rm4,sa0, rn=5, rd=6
// 1 10 0 101 0000 00100 000000 00101 00110
#define EOR_NO_SHIFT 0xCA0400A6 

// Logic 32bit, eon, lsr, rm=7, sa=0, rn=8, rd=9
// 0 10 0 101 0011 00111 000000 01000 01001
#define  EON_NO_SHIFT 0x4A670109

// Logic 32bit ands, asr, rm=4, sa=00, rn=5, rd=6
// 0 11 0 101 0100 00100 101000 00101 00110
#define ANDS_NO_SHIFT 0x6A84A0A6

// Logic 32bit, bics, ror, rm=7, sa=00, rn=8, rd=9
// 0 11 0 101 0111 00111 001111 01000 01001
#define BICS_NO_SHIFT 0x6AE73D09

//madd, ra = 11111 (zeroreg), rm = 8, rn = 16, rd = 1
//1001 1011 0000 1000 0111 1110 0000 0001
#define MADD 0x9b087e01

//msub, ra = 24, rm = 8, rn = 16, rd = 1
//1001 1011 0000 1000 1110 0010 0000 0001
#define MSUB 0x9B08E201

void dpiReg_test() {
	struct processor p = {{0x0}, 0x0, {false, true, false, false}, {0x0}};
	p.genregs[1] = 0x1;
	p.genregs[2] = 0x2;
	dpireg(&p, TEST1);
	testcond(p.genregs[3]==0x3, "Arithmetic 32bit, add lsl, rm=1, shift_amount = 0, rn = 2, rd = 3\n");	
	dpireg(&p, TEST2);
	testcond(p.genregs[3]==0x1000000000000002, "Arithmetic 64bit, add set flags,lsl,  rm = 1, shift amount = 60, rn = 2, rd = 3");
	
	p.genregs[10] = 0x4000000; 
	p.genregs[11] = 0x3;
	dpireg(&p, TEST3);
	testcond(p.genregs[13]==0x1,"Arithmetic 32b, sub, lsr, rm=10, shiftamount=25, rn=11, rd=13, 0x3-0x2");

	p.genregs[10] = 0x4000000; 
	p.genregs[11] = 0x2;
	dpireg(&p, TEST3);
	testcond(p.genregs[13]==0x0,"Arithmetic 32b, sub, lsr, rm=10, shiftamount=25, rn=11, rd=13, 0x2-0x2");
	
	p.genregs[10] = 0x1;
	p.genregs[11] = 0x1;
	dpireg(&p, SUBS_NO_SHIFT);
	testcond(p.pstate[1]==true, "SUBS Z flag set");
	
	p.genregs[10] = 0x8;
	p.genregs[11] = 0x4;
	dpireg(&p,SUBS_NO_SHIFT);
	testcond(p.pstate[0]==true && p.pstate[2]==true, "SUBS C and N flags are set.");
	
	p.genregs[10] = 0x8;
	p.genregs[11] = 0x7;
	dpireg(&p, SUBS_NO_SHIFT);
	testcond(p.pstate[3]==true, "SUBS V set");

	p.genregs[4]=0x1;
	p.genregs[5]=0xFFFFFFFFFFFFFFFF;
	dpireg(&p,TEST5);
	testcond(p.genregs[6]==0x10000000000, "Logic 64bit, and, lsl, rm=4, sa=40, rn=5, rd=6");
	
	p.genregs[7]=0xF;
	p.genregs[8]=0xFFFFFFFF;
	dpireg(&p,BIC_NO_SHIFT);
	testcond(p.genregs[9]==0xFFFFFFF0, "Logic 32bit bic, lsr, rm7,sa0,rn8,rd9");
	
	
	p.genregs[7]=0x78000;
	p.genregs[8]=0xFFFFFFFF;
	dpireg(&p,BIC_SHIFT);
	testcond(p.genregs[9] ==0xFFFFFFF0,"BIC_SHIFT");

	p.genregs[4]=0x400000000;
	p.genregs[5]=0x2;
	dpireg(&p,TEST7);
	testcond(p.genregs[6]==0x2, "Logic 64bit orr, asr, rm=4, sa=40, rn=5, rd=6");

	p.genregs[4] = 0xA;
	p.genregs[5] = 0x5;
	dpireg(&p,ORR_NO_SHIFT);
	testcond(p.genregs[6]==0xF, "Logic 64, orr, asr, rm4,sa=0,rn=5,rd=6");
	
	p.genregs[7]= 0xFFFFFFFA;
	p.genregs[8] = 0xA;
	dpireg(&p, ORN_NO_SHIFT);
	testcond(p.genregs[9]==0xF, "Logic 32 orn ror rm7 sa0 rn8 rd9");
	
	p.genregs[7] = 0xFFFD7FFF;
	p.genregs[8] = 0xA;
	dpireg(&p,TEST8);
	testcond(p.genregs[9]==0xF, "Logic 32bit orn, ror, rm=7, sa=15, rn=8, rd=9");
	
	p.genregs[4] = 0xFFFFFFFF5FFFFFFF;
	p.genregs[5] = 0xFFFFFFFFAFFFFFFF;
	dpireg(&p, EOR_NO_SHIFT);
	testcond(p.genregs[6]==0xF0000000, "EOR NO SHIFT");
	
	p.genregs[7]=0xFFFFFFFFFFFFFFFA;
	p.genregs[8]=0x5;
	dpireg(&p,EON_NO_SHIFT);
	testcond(p.genregs[9]==0x0, "EON_NO_SHIFT");
	
	p.genregs[4]=0xC0000000;
	p.genregs[5]=0x80000000;
	dpireg(&p, ANDS_NO_SHIFT);
	testcond(p.pstate[2]==false, "ANDS_NO_SHIFT: C is not set");
	testcond(p.pstate[3]==false, "ANDS_NO_SHIFT: V is not set");
	testcond(p.pstate[0]==true, "ANDS_NO_SHIFT: N is set");

	p.genregs[7]=0xFFFFFFFF;
	p.genregs[8]=0x0;
	dpireg(&p, BICS_NO_SHIFT);
	testcond(p.pstate[2]==false, "BICS_NO_SHIFT: C is not set");
	testcond(p.pstate[3]==false, "BICS_NO_SHIFT: V is not set");
	testcond(p.pstate[0]==false, "BICS_NO_SHIFT: N is not set"); 

	
	//madd
	p.genregs[8] = 0xe;
	p.genregs[16] = 0x20;
	p.genregs[1] = 0xaaaaaaaaaaaaaaaa;

	//result = 14 * 32 = 448 = 1c0 
	dpireg(&p, MADD); 
	printf("rd: %lu\n", p.genregs[1]);
	testcond(p.genregs[1] == 0x1c0, "madd");

	//msubp.genregs[24] = 0x1f4;
	//result = 500 - 448 = 52 = 0x34
	dpireg(&p, MSUB);
 	testcond(p.genregs[1] == 0x34, "msub");
}	

