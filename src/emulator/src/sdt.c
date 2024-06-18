#include <stdint.h>
#include "processor_def.h"
#include "sdt.h"
#define REG_MASK 0x1f
#define XN_SHIFT 5
#define OFFSET_MASK 0xfff
#define OFFSET_SHIFT 10
#define L_MASK 0x400000
#define U_MASK 0x1000000
#define SF_MASK 0x40000000
#define X_REGMASK 0xffffffffffffffff
#define X_UO_MUL 8
#define W_REGMASK 0xffffffff
#define W_UO_MUL 4
#define RO_MASK 0x800
#define XM_SHIFT 6
#define INDEX_MASK 0x2
#define SIMM9_MASK 0x1ff
#define SIMM9_SHIFT 2
#define SIMM9_MSB 255
#define SIMM9_SIGN_E 0xfffffffffffffe00
#define BYTE 0xff
#define CELL_SIZE 4
#define BYTE_SIZE 8
#define BYTES 8

void sdt(struct processor *p, uint32_t ir){
	unsigned int rt = ir & REG_MASK;
	unsigned int xn = (ir >> XN_SHIFT) & REG_MASK;
	uint64_t offset = (ir >> OFFSET_SHIFT) & OFFSET_MASK;
	unsigned int l = ir & L_MASK;// 1=load, 0=store
	unsigned int u = ir & U_MASK;//1=unsigned offset
	unsigned int sf = ir & SF_MASK;
	uint64_t regmask = X_REGMASK;
	unsigned int uomul = X_UO_MUL;
	if (sf == 0) {
		regmask = W_REGMASK;
		uomul = W_UO_MUL;
	}
	uint64_t address;
	if (u > 0) {
		//unsigned offset
		uint64_t uoffset = offset * uomul;
		address = (*p).genregs[xn] + uoffset;
	}
	else {
		//not unisgned offset
		if ((offset & RO_MASK) > 0){
			//register offset
			unsigned int xm = (offset >> XM_SHIFT) & REG_MASK;
			address = (*p).genregs[xn] + (*p).genregs[xm];		
		}
		else {
			//pre/post index
			unsigned int i = offset & INDEX_MASK;
			uint64_t simm9 = (offset >> SIMM9_SHIFT) & SIMM9_MASK;
			if (simm9 > SIMM9_MSB) {
				simm9 = simm9 + SIMM9_SIGN_E;
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

	uint64_t value = 0x0;
	unsigned int remainder;
	if (l > 0) {
		//load
		address += BYTES - 1;
		for (int x = 0; x < BYTES; x++){
			remainder = address % CELL_SIZE;
			value = (value << BYTE_SIZE) + (((*p).memory[address/CELL_SIZE] >> remainder * BYTE_SIZE) & BYTE);
			address--;
		}
		value = value & regmask;
		(*p).genregs[rt] = ((*p).genregs[rt] & ~regmask) + value;
	}
	else {
		//store
		value = (*p).genregs[rt] & regmask;
		for (;uomul > 0; uomul--){
			remainder = address % CELL_SIZE;
			(*p).memory[address/CELL_SIZE] = ((*p).memory[address/CELL_SIZE] & ~(BYTE << (remainder * BYTE_SIZE))) + ((value & BYTE) << (remainder * BYTE_SIZE));
			value = value >> BYTE_SIZE;
			address ++;
		}

	}
	
	
	
}
