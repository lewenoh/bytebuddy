#include <stdint.h>
#include <stdbool.h>
#include "processor_def.h"
#include "branch.h"
#define UNCOND_MSB_MASK 0x2000000
#define COND_MSB_MASK 0x800000
#define UNCOND_OFFSET 0x03ffffff
#define COND_OFFSET 0x7ffff
#define INSTR_SIZE 4
#define BRANCH_TYPE_SHIFT 30
#define BRANCH_TYPE_MASK 0x3
#define UNCOND_SIGN_E 0xfffffffff0000000
#define COND_SIGN_E 0xffffffffffe00000
#define REG_MASK 0x1f
#define COND_MASK 0xf

void branch(struct processor *p, uint32_t ir){
	unsigned int branchtype = (ir >> BRANCH_TYPE_SHIFT) & BRANCH_TYPE_MASK;
	unsigned int msboffset;
	uint64_t offset;
	unsigned int xn;
	switch (branchtype) {
		// whenever we do pc - 4 it is to negate the pc + 4 we do in
		// emulate, because when we branch we don't increment the
		// pc as usual.
		case 0:
			//unconditional
			msboffset = ir & UNCOND_MSB_MASK;
			offset = (ir & UNCOND_OFFSET) * INSTR_SIZE;
			if (msboffset > 0){
				offset = offset + UNCOND_SIGN_E;//instead of 0xfffffffc0000000 bc *4 shifts twice
			}
			(*p).pc = (*p).pc - INSTR_SIZE + offset;
			break;
		case 3:
			//register
			xn = (ir >> 5) & REG_MASK;
			(*p).pc = (*p).genregs[xn] - INSTR_SIZE;
			break;
		case 1: 
			//conditional
			msboffset = ir & COND_MSB_MASK;
			offset = ((ir >> 5) & COND_OFFSET) * INSTR_SIZE;
			if (msboffset > 0){
				offset = offset + COND_SIGN_E;
			}
			offset -= INSTR_SIZE;
			unsigned int cond = ir & COND_MASK;
			switch (cond) {
				case 0:
					//EQ
					if ((*p).pstate[1] == 1){
						(*p).pc = (*p).pc + offset;
					}
					break;
				case 1:
					//NE
					if ((*p).pstate[1] == 0){
                                                (*p).pc = (*p).pc + offset;
					}
					break;
				case 10:
					//GE
					if ((*p).pstate[0] == (*p).pstate[3]){
                                                (*p).pc = (*p).pc + offset;
                                        }
					break;
				case 11:
					//LT
					if ((*p).pstate[0] != (*p).pstate[3]){
						(*p).pc = (*p).pc + offset;
					}
					break;
				case 12:
					//GT
					if (((*p).pstate[1] == 0) && ((*p).pstate[0] == (*p).pstate[3])){
						(*p).pc = (*p).pc + offset;
					}
					break;
				case 13:
					//LE
					if (!(((*p).pstate[1] == 0) && ((*p).pstate[0] == (*p).pstate[3]))){
                                                (*p).pc = (*p).pc + offset;
                                        }
					break;
				case 14:
					//AL
					(*p).pc = (*p).pc + offset;
					break;
			}
			break;
	}
}
