#include <stdint.h>
#include "dpiImm.h"
#include "processor_def.h"
#define checkBits(value, bits, mask) ((value & mask) == bits)
#define REG_MASK 0x1f
#define OPERAND_MASK 0x3FFFF
#define OPERAND_SHIFT 5
#define OPI_MASK 0x7
#define OPI_SHIFT 23
#define OPC_MASK 0x3
#define OPC_SHIFT 29
#define SF_SHIFT 31
#define X_REGSIZE 64
#define W_REGSIZE 32
#define X_REGMASK 0xFFFFFFFFFFFFFFFF
#define W_REGMASK 0xFFFFFFFF
#define ARITH 0x2
#define IMM12_MASK 0xfff
#define IMM12_SHIFT 5
#define SH_SHIFT 17
#define WMOVE 0x5
#define IMM16_MASK 0xFFFF
#define HW_MASK 0x3
#define HW_SHIFT 16
#define HW_MUL 16

void setFlags_arithmetic(uint64_t result, int regsize, struct processor *p) {
	// set N flag
	p->pstate[0] = (result >> (regsize - 1)) & 0x1;
	
	// set Z flag
	p->pstate[1] = (result == 0);
}

void dpiImm( struct processor *p, uint32_t ir ) {
	uint64_t rd = ir & REG_MASK; // bits [4:0]
	uint64_t operand = (ir >> OPERAND_SHIFT) & OPERAND_MASK; // bits [22:5]
	uint64_t opi = (ir >> OPI_SHIFT) & OPI_MASK; // bits [25:23]
	uint64_t opc = (ir >> OPC_SHIFT) & OPC_MASK; // bits [30:29]
	uint64_t sf = ir >> SF_SHIFT; // bit 31

	int regsize = (sf == 1) ? X_REGSIZE : W_REGSIZE;
	uint64_t regmask = (sf == 1) ? X_REGMASK : W_REGMASK;
	uint64_t result;
	uint64_t mask;

	if (checkBits(opi, ARITH, OPI_MASK)) {
		uint64_t rn = operand & REG_MASK; // bits [5:0] of operand
                uint64_t imm12 = (operand >> IMM12_SHIFT) & IMM12_MASK; // bits [16:5] of operand
                uint64_t sh = (operand >> SH_SHIFT); // bit 17 of operand
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

	if (checkBits(opi, WMOVE, OPI_MASK)) {
		uint64_t imm16 = operand & IMM16_MASK;
		uint64_t hw = (operand >> HW_SHIFT) & HW_MASK;
		uint64_t opvalue = imm16 << (hw * HW_MUL);
		uint64_t result = 0;

	switch (opc) {
			case 0x0: //movn
				result = opvalue & regmask;
				p->genregs[rd] = (~result) & regmask;
				break;
			case 0x2: //movz
				p->genregs[rd] = opvalue;
				break;
			case 0x3: //movk
				mask = IMM16_MASK;
				mask = ~(mask<<(hw*HW_MUL));
				p->genregs[rd] = (p->genregs[rd] & mask) | opvalue;
				p->genregs[rd] &= regmask;
				break;
			default:
				break;
		}

	return;
	}

}
