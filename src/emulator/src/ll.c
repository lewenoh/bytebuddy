#include <stdint.h>
#include "processor_def.h"
#include "ll.h"

void ll(struct processor *p, uint32_t ir){
	unsigned int rt = ir & 0x1f;
	unsigned int sf = ir & 0x40000000;
	uint64_t regmask = 0xffffffffffffffff;
        unsigned int bytes = 8;
	if (sf == 0) {
                regmask = 0xffffffff;
		bytes = 4;
        }
	
	unsigned int msboffset = ir & 0x800000;
	uint64_t simm19 = (ir >> 5) & 0x7ffff;
	simm19 = simm19 * 4;
	if (msboffset > 0){
		simm19 = simm19 + 0xffffffffffe00000;
	}
	
	uint64_t address = (*p).pc + simm19;
	//uint64_t value = (*p).memory[(address/4) + 1];
	//value = ((value<<32) + (*p).memory[address/4]) & regmask;
	uint64_t value;
	unsigned int remainder;
	unsigned int byte = 0xff;
	address += (bytes - 1);
	for (int x = 0; x < bytes; x++){
		remainder = address % 4;
		value = (value << 8) + (((*p).memory[address/4] >> remainder * 8) & byte);
		address -= 1;
	}
	value = value & regmask;
	(*p).genregs[rt] = ((*p).genregs[rt] & ~regmask) + value;	
}


