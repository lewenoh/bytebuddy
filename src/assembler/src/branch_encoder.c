#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "table_def.h"
#include "branch_encoder.h"

#define UNCONDBASE 0x14000000 //base for unconditional branches
#define REGBASE 0xd61f0000 //base for uncond reg branches
#define CONDBASE 0x54000000 //base for conditional branches
#define NE 0x1 //cond encoding for ne
#define GE 0xa //encoding for ge
#define LT 0xb //encoding for lt
#define GT 0xc //encoding for gt
#define LE 0xd //encoding for le
#define AL 0xe //encoding for al
#define SIMM26MASK 0x3ffffff //mask for simm26
#define SIMM19MASK 0x7ffff //mask for simm19

static uint32_t getreg(char reg[30]){
	memmove(reg, reg+1, 29);
	return atoi(reg);
}
static uint32_t readimm(char imm[30]){
	memmove(imm, imm+1, 29);
	uint32_t result;
	if (imm[1]=='x'){
		memmove(imm, imm+2, 27);
		result = strtol(imm, NULL, 16);
	}
	else{
		result = atoi(imm);
	}
	return result;
}

uint32_t branch_encoder(uint32_t address, char instruction[6][30]){
	uint32_t hexi;
	//opcode =i[0], literal/xn = i[1]
	if (strcmp(instruction[0], "b")==0){
		//uncond branch to literal
		hexi = UNCONDBASE + (((readimm(instruction[1])-address) /4) & SIMM26MASK);
	}
	else if (strcmp(instruction[0], "br")==0){
		//uncond branch to xn
		hexi = REGBASE + (getreg(instruction[1]) <<5);
	}
	else{
		hexi = CONDBASE + ((((readimm(instruction[1])-address) /4) & SIMM19MASK) << 5);
		//conditional branch to literal
		memmove(instruction[0], instruction[0]+2, 28);
		if (strcmp(instruction[0], "ne")==0){ //eq encoding is 0, no if branch needed
			hexi = hexi + NE;
		}
		else if (strcmp(instruction[0], "ge")==0){
			hexi = hexi + GE;
		}
		else if (strcmp(instruction[0], "lt")==0){
			hexi = hexi + LT;
		}
		else if (strcmp(instruction[0], "gt")==0){
			hexi = hexi + GT;
		}
		else if (strcmp(instruction[0], "le")==0){
			hexi = hexi + LE;
		}
		else if (strcmp(instruction[0], "al")==0){
			hexi = hexi + AL;
		}
	}
	return hexi;
}

