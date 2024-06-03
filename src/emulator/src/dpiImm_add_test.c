#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "processor_def.h"
#include "dpiImm.h"
#include "dpiImm_add_test.h"
#include "testcond.h"

// 32B ADD without shift
// 32 bit, add, dpiImm, arithmetic, shift_amt = 0, imm = 2, rn = 1, rd = 6
// 0 00 100 010 0 000000000010 00001 00110 = 0x11000826
#define ADD_TEST1 0x11000826

// 32B ADD with shift
// 32 bit, add, dpiImm, arithmetic, shift_amt = 12, imm = 5 rn = 1, rd = 16
// 0 00 100 010 1 000000000101 00001 10000 = 0x91401430
#define ADD_TEST2 0x91401430

// 32B ADDS N
// 32 bit, adds, dpiImm, arithmetic, shift_amt = 0, imm = 1, rn = 2, rd = 7
// 0 01 100 010 0 000000000001 00010 00111 = 0x31000447
#define ADDS_TEST1 0x31000447

// 32B ADDS Z
// 32 bit, adds, dpiImm, arithmetic, shift_amt = 0, imm = 0, rn = 0, rd = 8
// 0 01 100 010 0 000000000000 00000 01000 = 0x31000008
#define ADDS_TEST2 0x31000008

// 32B ADDS C
// 32 bit, adds, dpiImm, arithmetic, shift_amt = 0, imm = 3, rn = 31, rd = 9
// 0 01 100 010 0 000000000011 11111 01001 = 0x31000FE9
#define ADDS_TEST3 0x31000FE9

// 32B ADDS C V
// 32 bit, adds, dpiImm, arithmetic, shift_amt = 1, imm = 0xFFF, rn = 31, rd = 10
// 0 01 100 010 1 111111111111 11111 01010 = 0x317FFFEA
#define ADDS_TEST4 0x317FFFEA

// 32B ADDS V
// 32 bit, adds, dpiImm, arithmetic, shift_amt = 0, imm = 1, rn = 30, rd = 11
// 0 01 100 010 0 000000000001 11110 01011 = 0x310007CB
#define ADDS_TEST5 0x310007CB

// 32B ADDS Z C
// 32 bit, adds, dpiImm, arithmetic, shift_amt = 0, imm = 1, rn = 31, rd = 11
// 0 01 100 010 0 000000000001 11111 01011 = 0x310007EB
#define ADDS_TEST6 0x310007EB

// 64B SUB without shift
// 64 bit, sub, dpiImm, arithmetic, shift_amt = 0, imm = 1, rn = 1, rd = 15
// 1 10 100 010 0 000000000001 00001 01111 = 0xD100042F
#define SUB_TEST1 0xD100042F

// 64B SUB with shift
// 64 bit, sub, dpiImm, arithmetic, shift_amt = 1, imm = 4, rn = 31, rd = 15
// 1 10 100 010 1 000000000100 11111 01111 = 0xD14013EF
#define SUB_TEST2 0xD14013EF

// 64B SUBS N
// 64 bit, sub, dpiImm, arithmetic, shift_amt = 0, imm = 6, rn = 1, rd = 15
// 1 11 100 010 0 000000000110 00001 01111 = 0xD100182F
#define SUBS_TEST3 0xF100182F

// 64B SUBS Z
// 64 bit, sub, dpiImm, arithmetic, shift_amt = 0, imm = 5, rn = 1, rd = 15
// 1 11 100 010 0 000000000101 00001 01111 = 0xD100142F
#define SUBS_TEST4 0xF100142F

// 64B SUBS C
// 64 bit, sub, dpiImm, arithmetic, shift_amt = 0, imm = 5, rn = 1, rd = 15
// 1 11 100 010 0 000000000101 00001 01111 = 0xF100142F
#define SUBS_TEST5 0xF100142F

// 64B SUBS V
// 64 bit, sub, dpiImm, arithmetic, shift_amt = 1, imm = 0xFFF, rn = 3, rd = 16
// 1 11 100 010 1 111111111111 00011 10000 = 0xF17FFC70
#define SUBS_TEST6 0xF17FFC70

// 64B SUBS C V

// printf("%d, %d, %d, %d", p.pstate[0], p.pstate[1], p.pstate[2], p.pstate[3]);

//movn, 32 bit reg, imm = 27, hw = 1, rd = 7
//0001 0010 1010 0000 0000 0011 0110 0111
#define MOVN32 0x12a00367

//movn, 64 bit reg, same as movn32, but hw = 3
//1001 0010 1110 0000 0000 0011 0110 0111
#define MOVN64 0x92e00367

//movz, 32 bit reg, same as movn32, but opc = 10
#define MOVZ32 0x52a00367

//movz, 64 bit reg, same as movn63, but opc = 10
#define MOVZ64 0xd2e00367

//movk, 32 bit reg, same as movn32, but opc = 11
#define MOVK32 0x72a00367

//movk, 64 bit reg, same as movn64, but opc = 11
#define MOVK64 0xF2E00367

void dpiImm_add_tests() {
	struct processor p = {{0x0}, 0x0, {false, true, false, false}, {0x0}};

	// ADD_TEST1
	p.genregs[1] = 5;
	dpiImm(&p, ADD_TEST1);
	testcond( p.genregs[6] == 7, "ADD without shift");

	// ADD_TEST2
	dpiImm(&p, ADD_TEST2);
	testcond(p.genregs[16] == 20485, "ADD with shift");

	// ADDS_TEST1
	p.genregs[2] = 0x80000000;
	dpiImm(&p, ADDS_TEST1);
	testcond((p.genregs[7] == 2147483649 && p.pstate[0] == 1 && p.pstate[1] == 0 && p.pstate[2] == 0 && p.pstate[3] == 0), "ADDS with N flag set");

	// ADDS_TEST2
	p.genregs[0] = 0x0;
	dpiImm(&p, ADDS_TEST2);
	testcond( (p.genregs[8] == 0 && p.pstate[0] == 0 && p.pstate[1] == 1 && p.pstate[2] == 0 && p.pstate[3] == 0), "ADDS with Z flag set");

	//ADDS_TEST3
	p.genregs[31] = 0xFFFFFFFF;
	dpiImm(&p, ADDS_TEST3);
	testcond( (p.genregs[9] == 2 && p.pstate[0] == 0 && p.pstate[1] == 0 && p.pstate[2] == 1 && p.pstate[3] == 0), "ADDS with C flag set");

	// ADDS_TEST4 V flag 00FFEFFF
	dpiImm(&p, ADDS_TEST4);
	testcond((p.genregs[10] == 0x00FFEFFF && p.pstate[0] == 0 && p.pstate[1] == 0 && p.pstate[2] == 1 && p.pstate[3] == 1), "ADDS with C V flag set");


	// ADDS_TEST5 V
	p.genregs[30] = 0x7FFFFFFF; 
        dpiImm(&p, ADDS_TEST5);
	testcond((p.genregs[11] == 0x80000000 && p.pstate[0] == 1 && p.pstate[1] == 0 && p.pstate[2] == 0 && p.pstate[3] == 1), "ADDS with V flag set");

	// ADDS_TEST6
        dpiImm(&p, ADDS_TEST6);
	testcond((p.genregs[11] == 0x0 && p.pstate[0] == 0 && p.pstate[1] == 1 && p.pstate[2] == 1 && p.pstate[3] == 0), "ADDS with Z C flag set");

	// SUB_TEST1
	dpiImm(&p, SUB_TEST1);
	testcond(p.genregs[15] == 4, "SUB without shift");

	//SUB_TEST2
	p.genregs[31] = 0X5000;
	dpiImm(&p, SUB_TEST2);
	testcond(p.genregs[15] == 0x1000, "SUB with shift");

	//SUB_TEST3
	dpiImm(&p, SUBS_TEST3);
	testcond((p.genregs[15] == 0xffffffffffffffff && p.pstate[0] == 1 && p.pstate[1] == 0 && p.pstate[2] == 0 && p.pstate[3] == 0), "SUBS with N flag set");

	//SUB_TEST4
	dpiImm(&p, SUBS_TEST4);
	testcond((p.genregs[15] == 0 && p.pstate[0] == 0 && p.pstate[1] == 1 && p.pstate[2] == 1 && p.pstate[3] == 0), "SUBS with Z C flag set"); 

	//SUB_TEST5
	p.genregs[1] = 7;
	dpiImm(&p, SUBS_TEST5);
	testcond( (p.genregs[15] == 2 && p.pstate[0] == 0 && p.pstate[1] == 0 && p.pstate[2] == 1 && p.pstate[3] == 0), "SUBS with only C flag set");

	//SUBS_TEST6
	p.genregs[3] = 0x8000000000000001;
	dpiImm(&p, SUBS_TEST6);
	printf("%lx", p.genregs[16]);
	testcond ((p.genregs[16] == 0x7FFFFFFFFF001000 && p.pstate[0] == 0 && p.pstate[1] == 0 && p.pstate[2] == 0 && p.pstate[3] == 1), "SUBS with only V flag set");

	//movn32
	//0x1b << 16 = 0x1b0000;
	//~op = 0xffe4ffff;
	p.genregs[7] = 0x1111111111111111;
	dpiImm(&p, MOVN32);
	testcond(p.genregs[7] == 0xffe4ffff, "movn, 32 bit reg");

	//movn64
	//0x1b << 48= 0x1b000000000000
	//~op = 0xffe4ffffffffffff
	dpiImm(&p, MOVN64);
	testcond(p.genregs[7] == 0xffe4ffffffffffff, "movn, 64 bit reg");

	//movz32
	dpiImm(&p, MOVZ32);
	testcond(p.genregs[7] == 0x1b0000, "movz, 32 bit reg");

	//movz64
	dpiImm(&p, MOVZ64);
	testcond(p.genregs[7] == 0x1b000000000000, "movz, 64 bit reg");

	//movk32
	p.genregs[7] = 0xaaaaaaaaaaaaaaaa;
	dpiImm(&p, MOVK32);
	testcond(p.genregs[7] == 0x001BAAAA, "movk, 32 bit reg");
	
	//movk64
	dpiImm(&p, MOVK64);
	testcond(p.genregs[7] == 0x001B0000001BAAAA, "movz, 64 bit reg");
}

