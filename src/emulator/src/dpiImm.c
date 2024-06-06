#include <stdio.h>
#include <stdint.h>
#include "dpiImm.h"
#include "processor_def.h"
#define checkBits(value, bits, mask) ((value & mask) == bits)

void setFlags_arithmetic(uint64_t result, int regsize, struct processor *p) {
	// set N flag
	p->pstate[0] = (result >> (regsize - 1)) & 0x1;
	
	// set Z flag
	p->pstate[1] = (result == 0);
}

void dpiImm( struct processor *p, uint32_t ir ) {
	uint64_t rd = ir & 0x1f; // bits [4:0]
	uint64_t operand = (ir >> 5) & 0x3FFFF; // bits [22:5]
	uint64_t opi = (ir >> 23) & 0x7; // bits [25:23]
	uint64_t opc = (ir >> 29) & 0x3; // bits [30:29]
	uint64_t sf = ir >> 31; // bit 31

	int regsize = (sf == 1) ? 64 : 32;
	uint64_t regmask = (sf == 1) ? 0xFFFFFFFFFFFFFFFF : 0xFFFFFFFF;
	uint64_t result;
	uint64_t mask;


	uint64_t opimask = 0x7;

	if (checkBits(opi, 0x2, opimask)) {
		uint64_t rn = operand & 0x1f; // bits [5:0] of operand
                uint64_t imm12 = (operand >> 5) & 0xfff; // bits [16:5] of operand
                uint64_t sh = (operand >> 17); // bit 17 of operand
		uint64_t imm_size = 12 * (sh + 1);
		
		if (sh == 1) {
			imm12 = imm12 << 12;
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
				result = p->genregs[rn] - imm12;
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

	if (checkBits(opi, 0x5, opimask)) {
		uint64_t imm16 = operand & 0xffff;
		uint64_t hw = (operand >> 16) & 0x3;
		uint64_t opvalue = imm16 << (hw * 16);
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
				mask = 0xffff;
				mask = ~(mask<<(hw*16));
				p->genregs[rd] = (p->genregs[rd] & mask) | opvalue;
				p->genregs[rd] &= regmask;
				break;
			default:
				break;
		}

	return;
	}

}
