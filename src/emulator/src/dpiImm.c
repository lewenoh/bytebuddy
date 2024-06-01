#include <stdio.h>
#include <stdint.h>
#include "dpiImm.h"
#include "processor_def.h"
#define checkBits(value, bits, mask) ((value & mask) == bits)

void setFlags_arithmetic(uint64_t result, int regsize) {
	// set N flag
	p.pstate[0] = (result >> (regsize - 1));

	// set Z flag
	p.pstate[1] = result == 0;
}

void dpiImm( struct processor p, uint32_t ir ) {
	uint64_t rd = ir & 0x1f;
	uint64_t operand = ir >> 5 & 0x3fff;
	uint64_t opi = ir >> 23 & 0x7;
	uint64_t opc = ir >> 29 & 0x3;
	uint64_t sf = ir >> 31;

	uint64_t result = 0;

	if (sf == 0) {
		int regsize = 32;
		uint32_t regmask = 0xffffffff;
		uint32_t msbmask = 0x80000000;
	} else {
		int regsize = 64;
		uint64_t regmask = 0xffffffffffffffff;
		uint64_t msbmask = 0x8000000000000000;
	}

	if (rd == 0x1f) {
		return;
	}

	uint64_t opimask = 0x7;
	uint64_t opcmask = 0x3;

	if (checkBits(opi, 0x2, opimask)) {
		uint64_t rn = operand & 0x3fff;
                uint64_t imm12 = (operand >> 5) & 0xfff;
                uint64_t sh = operand >> 22;
		uint64_t imm_size = 12;

		if (sh == 1) {
			imm12 >>= 12;
			imm_size = 24;
		}

		switch (opc) {
                        case 0x0:
                                p.genregs[rd] = p.genregs[rn] + imm12;
                                break;

                        case 0x1:
                                p.genregs[rd] = p.genregs[rn] + imm12;
                                setFlags_arithmetic(p.genregs[rd], regsize);

                                // setting C flag
                                p.pstate[2] = (p.genregs[rd] < p.genregs[rn] || p.genregs[rd] < imm12 );

				// setting V flag
				int imm_sign = imm12 >> (imm_size - 1);
				int rn_sign = p.genregs[rn] >> (regsize - 1);
				int rd_sign = p.genregs[rd] >> (regsize - 1);
				p.pstate[3] = (imm_sign == rn_sign && rd_sign != rn_sign); 

                                break;
	
                        case 0x2:
                                p.genregs[rd] = processor.GenReg[rn] - imm12;
                                break;

                        case 0x3:
                                p.genregs[rd] = processor.GenReg[rn] - imm12;
                                setFlags_arithmetic(p.genregs[rd], regsize);

				// setting C flag
				p.pstate[2] = (p.genregs[rd] > p.genregs[rn] || p.genregs[rd] > imm12);

				// setting V flag
				int imm_sign = imm12 >> (imm_size - 1);
                                int rn_sign = p.genregs[rn] >> (regsize - 1);
                                int rd_sign = p.genregs[rd] >> (regsize - 1);
				p.pstate[3] = (imm_sign == rn_sign && rd_sign != rn_sign);

                                break;
                      
		      	default:
                                break;
                }
		return;
	}

	if (checkBits(opi, 0x5, opimask)) {
		int imm16 = operand & 0xffff;
		int hw = operand >> 16 & 0x3;
		int opvalue = imm16 << (hw * 0x10);

		switch (opc) {
			case 0x0:
				int opvalue |= (imm16 << (hw * 16));
				processor.GenReg[rd] = ~opvalue;
				break;
			case 0x2:
				processor.GenReg[rd] = opvalue;
				break;
			case 0x3:
				int mask |= opvalue;
				processor.GenReg[rd] = mask;
				break;
			default:
				break;
		}
	}

}
