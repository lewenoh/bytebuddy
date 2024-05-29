#include <stdio.h>
#include <stdint.h>
#include "dpiImm.h"
#include "ProcessorDef.h"

void dpiImm( uint64_t ir, p processor ) {
	int rd = ir & 0x1f;
	int operand = ir >> 5 & 0x3fff;
	int opi = ir >> 23 & 0x7;
	int opc = ir >> 29 & 0x3;
	int sf = ir >> 31;

	if (rd == 0x1f) {
		return;
	}

	if (opi == 0x2) {
		int rn = operand & 0x3fff;
		int imm12 = (operand >> 5) & 0xfff;
		int sh = operand >> 22;
		if (sh = 1) {
			Imm12 >>= 12;
		}

		switch (opc) {
			case 0x0:
			       	processor.GenReg[rd] = processor.GenReg[rn] + imm12;
				break;
			case 0x1: 
				processor.GenReg[rd] = processor.GenReg[rn] + imm12;
				setFlags();
				break;
			case 0x2: 
				processor.GenReg[rd] = processor.GenReg[rn] - imm12;
				break;
			case 0x3: 
				processor.GenReg[rd] = processor.GenReg[rn] - imm12;
				setFlags();
				break;
			default:
				break;
		}

	}

	if (opi == 101) {
		int imm16 = operand & 0xffff;
		int hw = operand >> 16 & 0x3;
		int opvalue = imm16 << (hw * 0x10);

		switch (opc) {
			case 0x0:
				int opvalue |= (imm16 << (hw * 16));
				processor.GenReg[rd] = ~opvalue;
				break;
			case 0x2:
				processor.GenReg[rd] = opvalue;
				break;
			case 0x3:
				int mask |= opvalue;
				processor.GenReg[rd] = mask;
				break;
			default:
				break;
		}
	}

}
