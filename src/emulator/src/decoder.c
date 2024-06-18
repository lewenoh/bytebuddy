#include <stdio.h>
#include "decoder.h"
#include "processor_def.h"
#define OP0_SHIFT 25
#define SINGLE_BIT_SHIFT 1
#define LSB_MASK 0x1
#define SF_BIT_SHIFT 4
uint64_t ir_copy;
uint64_t fourth_bit_1;
uint64_t third_bit_1;
uint64_t snd_bit_1;
uint64_t bit_31_1;


//enum type for instruction type

i_type decode(uint64_t ir) {
	// Get Op0 to start at lsb
	ir_copy = ir >> OP0_SHIFT;
	// Get 4th op0 bit state and shift right once.
	fourth_bit_1 = LSB_MASK & ir_copy; 
	ir_copy >>= SINGLE_BIT_SHIFT;

	// Get 3th op0 bit state and shift right once.
	third_bit_1 = LSB_MASK & ir_copy;
	ir_copy >>= SINGLE_BIT_SHIFT;

	// Get 2nd op0 bit state and shift right 4.
	snd_bit_1 = LSB_MASK & ir_copy;
	ir_copy >>= SF_BIT_SHIFT;

	// Get sf bit state.
	bit_31_1 = LSB_MASK & ir_copy;
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
