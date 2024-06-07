#include <stdint.h>
#include <stdbool.h>
#include "processor_def.h"
#include "dpiReg.h"

void dpireg(struct processor *p, uint32_t ir){
	unsigned int rd = ir & 0x1f; //destination register, 5 bits
	unsigned int rn = (ir >> 5) & 0x1f; //r2, 5 bits
	unsigned int operand = (ir >> 10) & 0x3f; //operand , 6 bits
	unsigned int rm = (ir >> 16) & 0x1f; //r1, 5 bits
	unsigned int opr = (ir >> 21) & 0xf; //determines type of dpi w m, 4 bits
	unsigned int m = (ir >> 28) & 0x1; //'', 1 bit
	unsigned int opc = (ir >> 29) & 0x3; //opcode, determines op, 2 bits
	unsigned int sf = (ir >> 31); //1 bit, 0=32 bit regs, 1=64 bit regs
	uint64_t regmask = 0xffffffffffffffff;
	uint64_t msbmask = 0x8000000000000000;
	int regsize = 64;
	uint64_t result;
	uint64_t op1;
	uint64_t signbit;
	if (sf == 0) {
		regmask = 0xffffffff;
		msbmask = 0x80000000;
		regsize = 32;
	}

	if (m == 0){
    		unsigned int shift = (opr >> 1) & 0x3;
    		uint64_t op2 = (*p).genregs[rm] & regmask;
    		switch (shift) {
            		case 0:
                		//lsl
                		op2 = (op2 << operand) & regmask;
             		   	break;
            		case 1:
                		//lsr
                		op2 = (op2 >> operand) & regmask;
                		break;
            		case 2:
                		//asr
                		signbit = op2 & msbmask;
                		for (int x = 0; x<operand; x++){
                    			op2 = (op2 >> 1) + signbit;
                		}
				op2 = op2 & regmask;
                		break;
            		case 3:
                		if (opr < 8) {
                			//ror
                    			for (int x = 0; x<operand; x++){
                        			op2 = (op2 >> 1) + ((op2 & 0x1) << (regsize-1));
                    			}
                		}
               		 	break;
		}
		if ((opr & 0x1) == 1) {
    			// negate
        		op2 = (~op2)&regmask;
   		 }
		uint64_t op1 = (*p).genregs[rn] & regmask;
    		if (opr >= 8) {
    			//arithmetic
        		if ((opc & 0x2) == 0){
                		//add
            			result = op1 + op2;
        		}
        		else {
                		//sub
            			result = op1 - op2;
        		}
			result = result & regmask;
        		if ((opc & 0x1) == 1){
                		//set flags from result
				// set N
            			(*p).pstate[0] = (result & msbmask) >> (regsize-1);
				// set Z
            			if (result == 0) {
                			(*p).pstate[1] = 1;
            			}
            			else {
                			(*p).pstate[1] = 0;
           			}
				// set C
				if ((opc == 1) & ((result<op1) || (result<op2))){
					(*p).pstate[2] = 1;
				}
				else if ((opc == 3) & (op1 >= op2)){
					(*p).pstate[2] = 1;
				}
				else {
					(*p).pstate[2] = 0;
				}
				// set V
				if ((opc == 1) && ((op1 & msbmask) == (op2 & msbmask)) && ((result & msbmask) != (op1 & msbmask))){
					(*p).pstate[3] = 1;
				}
				else if ((opc == 3) && ((op1 & msbmask) != (op2 & msbmask)) && ((result & msbmask) == (op2 & msbmask))){
					(*p).pstate[3] = 1;
				}
				else {
					(*p).pstate[3] = 0;
				}

        		}
			(*p).genregs[rd] = result;
		}
		else if (opr < 8) {
    			//bit-logic
	        	switch (opc) {
  	      			case 0:
        	        		result = op1 & op2;
                			break;
            			case 1:
                			result = op1 | op2;
                			break;
            			case 2:
                			result = op1 ^ op2;
                			break;
            			case 3:
                			result = op1 & op2;
                			(*p).pstate[0] = (result & msbmask) >> (regsize-1);
                			if (result == 0) {
                    				(*p).pstate[1] = 1;
                			}
               				else {
                    				(*p).pstate[1] = 0;
                			}
                			(*p).pstate[2] = 0;
                			(*p).pstate[3] = 0;
               				 break;

			}
			(*p).genregs[rd] = result;
    		}
	}
	
	else if ((m == 1) && (opr == 8) && (opc == 0)){
		//multiply
    		unsigned int ra = operand & 0x1f;

		unsigned int x = operand >> 5;
    		if (ra == 31){
        		op1 = ZEROREG;
    		}
    		else {
        		op1 = (*p).genregs[ra] & regmask;
   		}
    		uint64_t op2 = ((*p).genregs[rn] & regmask) * ((*p).genregs[rm] & regmask);
		op2 = op2 & regmask;
    		if (x == 0) {
       			result = op1 + op2;
    		}
    		else {
        		result = op1 - op2;
   		}
		result = result & regmask;
    		(*p).genregs[rd] = result & regmask;
	}
}
