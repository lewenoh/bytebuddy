#include <stdint.h>
#include <stdbool.h>
#include "processor_def.h"
#include "dpiReg.h"

#define REG_MASK 0x1f
#define OPERAND_MASK 0x3f
#define OPR_MASK 0xf
#define BIT_MASK 0x1
#define OPC_MASK 0x3
#define RN_SHIFT 5
#define OPERAND_SHIFT 10
#define RM_SHIFT 16
#define OPR_SHIFT 21
#define M_SHIFT 28
#define OPC_SHIFT 29
#define SF_SHIFT 31
#define X_REGMASK 0xFFFFFFFFFFFFFFFF
#define X_MSBMASK 0x8000000000000000
#define X_REGSIZE 64
#define W_REGMASK 0xFFFFFFFF
#define W_MSBMASK 0x80000000
#define W_REGSIZE 32
#define SHIFT_MASK 0x3
#define SHIFT_SHIFT 1
#define OPC_MSB 0x2
#define X_SHIFT 5
#define ZR 31

void dpireg(struct processor *p, uint32_t ir){
	unsigned int rd = ir & REG_MASK; //destination register, 5 bits
	unsigned int rn = (ir >> RN_SHIFT) & REG_MASK; //r2, 5 bits
	unsigned int operand = (ir >> OPERAND_SHIFT) & OPERAND_MASK; //operand , 6 bits
	unsigned int rm = (ir >> RM_SHIFT) & REG_MASK; //r1, 5 bits
	unsigned int opr = (ir >> OPR_SHIFT) & OPR_MASK; //determines type of dpi w m, 4 bits
	unsigned int m = (ir >> M_SHIFT) & BIT_MASK; //'', 1 bit
	unsigned int opc = (ir >> OPC_SHIFT) & OPC_MASK; //opcode, determines op, 2 bits
	unsigned int sf = (ir >> SF_SHIFT); //1 bit, 0=32 bit regs, 1=64 bit regs
	uint64_t regmask = X_REGMASK;
	uint64_t msbmask = X_MSBMASK;
	int regsize = X_REGSIZE;
	uint64_t result;
	uint64_t op1;
	uint64_t signbit;
	if (sf == 0) {
		regmask = W_REGMASK;
		msbmask = W_MSBMASK;
		regsize = W_REGSIZE;
	}

	if (m == 0){
    		unsigned int shift = (opr >> SHIFT_SHIFT) & SHIFT_MASK;
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
                        			op2 = (op2 >> 1) + ((op2 & BIT_MASK) << (regsize-1));
                    			}
                		}
               		 	break;
		}
		if ((opr & BIT_MASK) == 1) {
    			// negate
        		op2 = (~op2)&regmask;
   		 }
		uint64_t op1 = (*p).genregs[rn] & regmask;
    		if (opr >= 8) {
    			//arithmetic
        		if ((opc & OPC_MSB) == 0){
                		//add
            			result = op1 + op2;
        		}
        		else {
                		//sub
            			result = op1 - op2;
        		}
			result = result & regmask;
        		if ((opc & BIT_MASK) == 1){
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
    		unsigned int ra = operand & REG_MASK;

		unsigned int x = operand >> X_SHIFT;
    		if (ra == ZR){
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
