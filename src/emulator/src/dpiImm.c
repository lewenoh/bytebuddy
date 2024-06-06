#include <stdio.h>
#include <stdint.h>
#include "dpiImm.h"
#include "processor_def.h"
#define checkBits(value, bits, mask) ((value & mask) == bits)
#define OPERAND_SHIFT 5
#define OPI_SHIFT 23
#define OPC_SHIFT 29
#define SF_SHIFT 31
#define REG_BIT_MASK 0x1F
#define OPERAND_BIT_MASK 0x3FFFF
#define OPI_BIT_MASK 0x7
#define OPC_BIT_MASK 0x3
#define X_REG_SIZE 64
#define W_REG_SIZE 32
#define X_REG_MASK 0xFFFFFFFFFFFFFFFF
#define W_REG_MASK 0xFFFFFFFF
#define IMM12_MASK 0xFFF
#define SH_SHIFT 17
#define IMM12_INITIAL_SIZE 12
#define IMM16_MASK 0xFFFF
#define IMM16_SIZE 16
#define HW_MASK 0x3
#define ARITHMETIC_OPI 0x2
#define WIDE_MOVE_OPI 0x5

void setFlags_arithmetic(uint64_t result, int regsize, struct processor *p) {
	// set N flag
	p->pstate[0] = (result >> (regsize - 1));
	
	// set Z flag
	p->pstate[1] = (result == 0);
}

void dpiImm( struct processor *p, uint32_t ir ) {
	uint64_t rd = ir & REG_BIT_MASK; // extracting rd bits [4:0]
	uint64_t operand = (ir >> OPERAND_SHIFT) & OPERAND_BIT_MASK; // extracting operand bits [22:5]
	uint64_t opi = (ir >> OPI_SHIFT) & OPI_BIT_MASK; // extracting opi bits [25:23]
	uint64_t opc = (ir >> OPC_SHIFT) & OPC_BIT_MASK; // extracting opc bits [30:29]
	uint64_t sf = ir >> SF_SHIFT; //extracting sf bit 31

	int regsize = (sf == 1) ? X_REG_SIZE : W_REG_SIZE;
	uint64_t regmask = (sf == 1) ? X_REG_MASK : W_REG_MASK;

	if (rd == REG_BIT_MASK) {
		return;
	}

	if (checkBits(opi, ARITHMETIC_OPI, OPI_BIT_MASK)) {
		uint64_t rn = operand & REG_BIT_MASK; // extracting rn bits [5:0] from operand
                uint64_t imm12 = (operand >> OPERAND_SHIFT) & IMM12_MASK; // extracting imm12 bits [16:5] from operand
                uint64_t sh = (operand >> SH_SHIFT); // extracting sh bit 17 from operand
		uint64_t imm_size = IMM12_INITIAL_SIZE * (sh + 1);
		
		if (sh == 1) {
			imm12 = imm12 << IMM12_INITIAL_SIZE;
		}

		switch (opc) {
                        case 0x0: // add
                                p->genregs[rd] = (p->genregs[rn] + imm12) & regmask;
                                break;

                        case 0x1: // adds
                                p->genregs[rd] = (p->genregs[rn] + imm12) & regmask;
                                setFlags_arithmetic(p->genregs[rd], regsize, p);

                                // setting C flag
                                p->pstate[2] = (p->genregs[rd] < p->genregs[rn]);

				// setting V flag
				int imm_sign_add = imm12 >> (imm_size - 1);
				int rn_sign_add = p->genregs[rn] >> (regsize - 1);
				int rd_sign_add = p->genregs[rd] >> (regsize - 1);
				p->pstate[3] = (imm_sign_add == rn_sign_add && rd_sign_add != rn_sign_add); 

                                break;
	
                        case 0x2: // sub
                                p->genregs[rd] = (p->genregs[rn] - imm12) & regmask;
                                break;

                        case 0x3: // subs

				uint64_t result = p->genregs[rn] - imm12;
				p->genregs[rd] = result & regmask;
			       	setFlags_arithmetic(p->genregs[rd], regsize, p);
			       	// setting C flag
				p->pstate[2] = (p->genregs[rn] >= imm12);
                
				// setting V flag
			       	int imm_sign_sub = (imm12 >> (regsize - 1)) & 1;
				int rn_sign_sub = (p->genregs[rn] >> (regsize - 1)) & 1;
				int rd_sign_sub = (result >> (regsize - 1)) & 1;
				p->pstate[3] = (imm_sign_sub != rn_sign_sub && rn_sign_sub == rd_sign_sub);
                
				break;

		      	default:
                                break;
                }
		return;
	}

	if (checkBits(opi, WIDE_MOVE_OPI, OPI_BIT_MASK)) {
		uint64_t imm16 = operand & IMM16_MASK;
		uint64_t hw = (operand >> IMM16_SIZE) & HW_MASK;
		uint64_t opvalue = imm16 << (hw * IMM16_SIZE);
		uint64_t result = 0;

	switch (opc) {
			case 0x0:
				result = opvalue & regmask;
				p->genregs[rd] = (~result) & regmask;
				break;
			case 0x2:
				p->genregs[rd] = opvalue;
				break;
			case 0x3:
				uint64_t mask = ~(IMM16_MASK<<(hw*IMM16_SIZE));
				p->genregs[rd] = (p->genregs[rd] & mask) | opvalue;
				p->genregs[rd] &= regmask;
				break;
			default:
				break;
		}

	return;
	}

}
