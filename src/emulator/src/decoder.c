#include <stdio.h>
#include "decoder.h"
#include "processor_def.h"
uint64_t ir_copy;
uint64_t fourth_bit_1;
uint64_t third_bit_1;
uint64_t snd_bit_1;
uint64_t bit_31_1;


//enum type for instruction type

i_type decode(uint64_t ir) {
	// Checks for ones in each opcode bit.
	ir_copy = ir >> 25;
	fourth_bit_1 = 0x1 & ir_copy; 
	ir_copy >>= 1;
	third_bit_1 = 0x1 & ir_copy;
	ir_copy >>= 1;
	snd_bit_1 = 0x1 & ir_copy;
	ir_copy >>= 4;
	bit_31_1 = 0x1 & ir_copy;

	if (snd_bit_1==1) {
		if (fourth_bit_1==1) {return DPREG;} 
		else {
			if (bit_31_1==1) {return SDT;} 
			else {return LL;}
		}
	} else {
		if (third_bit_1==1) {return BRANCH;} 
		else {return DPIMM;}
	}

}
