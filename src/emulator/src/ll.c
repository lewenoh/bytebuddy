#include <stdint.h>
#include "processor_def.h"
#include "ll.h"
#define REG_MASK 0x1f
#define SF_MASK 0x40000000
#define X_REGMASK 0xffffffffffffffff
#define X_BYTES 8
#define W_REGMASK 0xffffffff
#define W_BYTES 4
#define OFFSET_MSB 0x800000
#define SIMM19_MASK 0x7ffff
#define SIMM19_SHIFT 5
#define SIMM19_MUL 4
#define SIMM19_SIGN_E 0xffffffffffe00000
#define BYTE 0xff
#define BYTE_SIZE 8
#define CELL_SIZE 4

void ll(struct processor *p, uint32_t ir){
	unsigned int rt = ir & REG_MASK;
	unsigned int sf = ir & SF_MASK;
	uint64_t regmask = X_REGMASK;
        unsigned int bytes = X_BYTES;
	if (sf == 0) {
                regmask = W_REGMASK;
		bytes = W_BYTES;
        }
	
	unsigned int msboffset = ir & OFFSET_MSB;
	uint64_t simm19 = (ir >> SIMM19_SHIFT) & SIMM19_MASK;
	simm19 = simm19 * SIMM19_MUL;
	if (msboffset > 0){
		simm19 = simm19 + SIMM19_SIGN_E;
	}
	
	uint64_t address = (*p).pc + simm19;
	uint64_t value;
	unsigned int remainder;
	address += (bytes - 1);
	for (int x = 0; x < bytes; x++){
		remainder = address % CELL_SIZE;
		value = (value << BYTE_SIZE) + (((*p).memory[address/CELL_SIZE] >> remainder * BYTE_SIZE) & BYTE);
		address--;
	}
	value = value & regmask;
	(*p).genregs[rt] = ((*p).genregs[rt] & ~regmask) + value;	
}


