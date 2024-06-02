#include <stdint.h>
#include <stdbool.h>
#include "branch.h"

void branch(struct processor *p, uint32_t ir){
	unsigned int branchtype = (ir >> 30) & 0x3;
	unsigned int msboffset;
	uint64_t offset;
	switch (branchtype) {
		case 0:
			//unconditional
			msboffset = ir & 0x2000000;
			offset = (ir & 0x03ffffff) * 4;
			if (msboffset > 0){
				offset = offset + 0xfffffffff0000000;//instead of 0xfffffffc0000000 bc *4 shifts twice
			}
			(*p).pc = (*p).pc + offset;
			break;
		case 3:
			//register
			unsigned int xn = (ir >> 5) & 0x1f;
			(*p).pc = (*p).genregs[xn];
			break;
		case 1: 
			//conditional
			msboffset = ir & 0x800000;
			offset = ((ir >> 5) & 0x7ffff) * 4;
			if (msboffset > 0){
				offset = offset + 0xffffffffffe00000;
			}
			unsigned int cond = ir & 0xf;
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
