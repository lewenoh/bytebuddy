#include "sdt.h"

void sdt(struct processor *p, uint32_t ir){
	unsigned int rt = ir & 0x1f;
	unsigned int xn = (ir >> 5) & 0x1f;
	uint64_t offset = (ir >> 10) & 0xfff;
	unsigned int l = ir & 0x400000;// 1=load, 0=store
	unsigned int u = ir & 0x1000000;//1=unsigned offset
	unsigned int sf = ir & 0x40000000;
	uint64_t regmask = 0xffffffffffffffff;
	unsigned int uomul = 8;
	if (sf == 0) {
		regmask = 0xffffffff;
		uomul = 4;
	}
	uint64_t address;
	if (u > 0) {
		//unsigned offset
		uint64_t uoffset = offset * uomul;
		address = (*p).genregs[xn] + uoffset;
	}
	else {
		//not unisgned offset
		if ((offset & 0x800) > 0){
			//register offset
			unsigned int xm = (offset >> 6) & 0x1f;
			address = (*p).genregs[xn] + (*p).genregs[xm]		
		}
		else {
			//pre/post index
			unsigned int i = offset & 0x2;
			uint64_t simm9 = (offset >> 2) & 0x1ff;
			if (simm9 > 255) {
				simm9 = simm9 + 0xfffffffffffffe00;
			}
			uint64_t incremented = (*p).genregs[xn] + simm9;
			if (i > 0){
				//pre index
				address = incremented;
			}
			else {
				//post index
				address = (*p).genregs[xn];
			}
			(*p).genregs[xn] = incremented;
		}
	}

	uint64_t value;
	if (l > 0) {
		//load
		value = ((*p).memory[address/4] + ((*p).memory[(address/4)+ 1] << 32)) & regmask;
		(*p).genregs[rt] = ((*p).genregs[rt] & ~regmask) + value;
	}
	else {
		//store
		value = (*p).genregs[rt] & regmask;
		(*p).memory[address/4] = value;
		if (sf > 0) {
			(*p).memory[(address/4) + 1] = value >> 32;
		}	

	}
	
	
	
}
