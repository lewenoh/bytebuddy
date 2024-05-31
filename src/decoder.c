#include <stdio.h>
#include "decoder.h"
#include "ProcessorDef.h"

//enum type for instruction type

i_type decode(uint64_t ir) {
	// Checks for ones in each opcode bit.
	ir_copy = ir >> 26;
	fourth_bit_1 = 0x1 & ir_copy; 
	ir_copy >>= 1;
	third_bit_1 = 0x1 & ir_copy;
	ir_copy >>= 1;
	snd_bit_1 = 0x1 & ir_copy;
	ir_copy >>= 1;
	first_bit_1 = 0x1 & ir_copy;

	if (snd_bit_1==1) {
		if (fourth_bit_1==1) {return DPREG;} 
		else {
			if (first_bit_1==1) {return SDT;} 
			else {return LL;}
		}
	} else {
		if (third_bit_1==1) {return B;} 
		else {return DPIMM;}
	}

}

int main() {
	printf("Yuhan is moses.");
	return 0;
}
