#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint32_t getreg(char reg[30]){
	//takes a register and returns the hex value encoding for it
	memmove (reg, reg+1, 3);
	uint32_t result;
	if (imm[1] == 'x'){
		//hex
		memmove(imm, imm+2, 27);
		result = strtol(imm, NULL, 16);
	}
	else {
		//decimal
		result = atoi(imm)
	}
	return result;
}

uint32_t getreg(char reg[30]){
	memmove (reg, reg+1, 29);
	return atoi(reg);
}
