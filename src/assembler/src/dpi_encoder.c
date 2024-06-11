#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "table_def.h"
#include "dpi_encoder.h"

#define MULBASE 0x1b000000 //base for muliply instructions
#define MSUBX 0x8000 //x bit for msub
#define WMOVEBASE 0x12800000 //base for wide move instructions, includes opi = 101
#define MOVZOPC 0x40000000 //opc for movz = 10
#define MOVKOPC 0x60000000 //opc for movk = 11
#define TWOOPBASE 0xa000000 //base for two op instructions
#define ARITHOPR 0x1000000 //opr for arithmetic operations
#define LSR 0x400000 //shift for lsrs, 01
#define ASR 0x800000 //shift for asrs, 10
#define ROR 0xc00000 //shift for rors, 11
#define ADDS 0x20000000 //opc = 01
#define SUB 0x40000000  //opc = 10
#define SUBS 0x60000000 //opc = 11
#define BIC 0x200000 //opc = 00, N = 1
#define ORR 0x400000 //01, 0
#define ORN 0x600000 //01, 1
#define EOR 0x800000 //10, 0
#define EON 0xa00000 //10, 1
#define ANDS 0xc00000 //11, 0
#define BICS 0xe00000 //11, 1

static bool codeingroup(char opcode[30], char group[12][5], int size){
	//returns true if the opcode is in the given group
	for (int x = 0;x < size;x++){
		if (strcmp(opcode, group[x]) == 0){
			return true;
		}
	}
	return false;
}

static uint32_t getsf(char reg[30]){
	//takes a register and returns 0 for 32 bit, 1 for 64 bit (if a w or x register)
	if (reg[0] == 'x'){
		return 0x80000000;
	}
	return 0x0;
}

static uint32_t getreg(char reg[30]){
	//takes a register and returns the hex encoding for it
	memmove(reg, reg+1, 3);
	return atoi(reg);
}

uint32_t dpi_encoder(char instruction[6][30]){
	uint32_t hexi;
	char opcode[30];
	strcpy(opcode, instruction[0]);
	char mul[2][5] = {"madd", "msub"};
	char twoop[12][5] = {"add", "adds", "sub", "subs", "and", "ands", "bic", "bics", "eor", "eon", "orr", "orn"};
	char arith[4][5] = {"add", "adds", "sub", "subs"};
	char oneop[9][5] = {"mov", "mul", "mneg", "neg", "negs", "mvn", "movn", "movk", "movz"}; 
	char wmoves[3][5] = {"movn", "movk", "movz"};
	char nodest[3][5] = {"cmp", "cmn", "tst"};
	char alias[5][30];
	if (codeingroup(opcode, mul, 2)){
		//multiply instruction
		//rd = i[1], rn = i[2], rm = i[3], ra = i[4]

		hexi = getsf(instruction[1]) + MULBASE;
		if (strcmp(opcode, "msub") == 0) {
			hexi = hexi + MSUBX;
		}
		
		hexi = hexi + (getreg(instruction[3]) << 16) + (getreg(instruction[4]) << 10) + (getreg(instruction[2]) << 5) + getreg(instruction[1]);

	}
	else if (codeingroup(opcode, twoop, 12)){
		//2 operand instruction
		//rd = i[1], rn = i[2], rm = i[3], shift = i[4], amount = i[5]
		hexi = getsf(instruction[1]) + TWOOPBASE + (getreg(instruction[3]) << 16) + (getreg(instruction[2]) << 5) + getreg(instruction[1]);
		//M is always 0, so no need to set
		//opr
		if (codeingroup(opcode, arith, 4)){
			//arith instruction
			hexi = hexi + ARITHOPR;
		}
		if (strcmp(instruction[4], "lsr") == 0){
			//no if needed for lsl, as shift = 00
			hexi = hexi + LSR;
		}
		else if (strcmp(instruction[4], "asr") == 0){
			hexi = hexi + ASR;
		}
		else if (strcmp(instruction[4], "ror") == 0){
			hexi = hexi + ROR;
		}

		//opc (and N), no if needed for and or add, as opc and N are 0
		if (strcmp(opcode, "adds") == 0) {
			hexi = hexi + ADDS;
		}
		else if (strcmp(opcode, "sub") == 0) {
			hexi = hexi + SUB;
		}
		else if (strcmp(opcode, "subs") == 0) {
			hexi = hexi + SUBS;
		}
		else if (strcmp(opcode, "bic") == 0) {
			hexi = hexi + BIC;
		}
		else if (strcmp(opcode, "orr") == 0) {
			hexi = hexi + ORR;
		}
		else if (strcmp(opcode, "orn") == 0) {
			hexi = hexi + ORN;
		}
		else if (strcmp(opcode, "eor") == 0) {
			hexi = hexi + EOR;
		}
		else if (strcmp(opcode, "eon") == 0) {
			hexi = hexi + EON;
		}
		else if (strcmp(opcode, "ands") == 0) {
			hexi = hexi + ANDS;
		}
		else if (strcmp(opcode, "bics") == 0) {
			hexi = hexi + BICS;
		}

		//operand
		memmove(instruction[5], instruction[5]+1, 29);
		hexi = hexi + (atoi(instruction[5]) << 10);

	}
	else if (codeingroup(opcode, oneop, 9)){
		//single operand with destination instruction
		//rd = i[1], imm = i[2], shift = i[3], amount = i[4]
		
		if (codeingroup(opcode, wmoves, 3)){
			//wide moves
			hexi = getsf(instruction[1]) + WMOVEBASE + getreg(instruction[1]);
			if (strcmp(opcode, "movz") == 0){ //opc = 10
				hexi = hexi + MOVZOPC;
			}
			else if (strcmp(opcode, "movk") == 0) { //opc = 11
				hexi = hexi + MOVKOPC;
			} // opc for movn = 00, so no need to do else
			
			if (instruction[3][0] != '\0'){
				memmove(instruction[4], instruction[4] + 1, 29);
				hexi = hexi + ((atoi(instruction[4]) / 16) << 21);	// hw
			}
			
			memmove(instruction[2], instruction[2]+3, 27);
			uint32_t imm = strtol(instruction[2], NULL, 16);
			hexi = hexi + (imm << 5);
		}
		else {
			//aliases
			strcpy(alias[1], instruction[1]);
			if ((strcmp(opcode, "neg") == 0)||(strcmp(opcode, "negs") == 0)){
				strcpy(alias[2], "x31");
				strcpy(alias[3], instruction[2]);
				strcpy(alias[4], instruction[3]);
				strcpy(alias[5], instruction[4]);
				if (strcmp(opcode, "neg") ==0){
					strcpy(alias[0], "sub");
				}
				else{
					strcpy(alias[0], "subs");
				}

			}
			else if ((strcmp(opcode, "mvn") == 0)||(strcmp(opcode, "mov") == 0)){
				strcpy(alias[2], "x31");
				strcpy(alias[3], instruction[2]);
				if (strcmp(opcode, "mvn")==0){
					strcpy(alias[0], "orn");
					strcpy(alias[4], instruction[3]);
					strcpy(alias[5], instruction[4]);
				}
				else {
					strcpy(alias[0], "orr");
				}
			}
			else { //mul, mneg *******
				strcpy(alias[2], instruction[2]);
				strcpy(alias[3], instruction[3]);
				strcpy(alias[4], "x31");//something wrong w rn
				if (strcmp(opcode, "mul")==0){
					strcpy(alias[0], "madd");
				}
				else{
					strcpy(alias[0], "msub");
				}
			}

			hexi = dpi_encoder(alias);
		}
	}
	else if (codeingroup(opcode, nodest, 3)){
		//2 operands, no destination instruction
		//rn = i[1], operand = i[2]
		if (strcmp(opcode, "cmp") == 0){
			strcpy(alias[0], "subs");
		}
		else if (strcmp(opcode, "cmn") == 0){
			strcpy(alias[0], "adds");
		}
		else {//tst
			strcpy(alias[0], "ands");
		
		}
		if (getsf(instruction[1]) > 0) {
			strcpy(alias[1], "x31");
		}
		else {
			strcpy(alias[1], "w31");
		}
		strcpy(alias[2], instruction[1]);
		strcpy(alias[3], instruction[2]);
		strcpy(alias[4], instruction[3]);
		strcpy(alias[5], instruction[4]);
		hexi = dpi_encoder(alias);
	}
	else {
		//is in no group
		hexi = 0;
	}

	return hexi;
}

