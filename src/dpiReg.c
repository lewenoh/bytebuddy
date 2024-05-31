#include "dpiReg.h"

void dpireg(struct processor p, uint32_t ir){
    int rd = ir & 0x1f; //destination register, 5 bits
    int rn = (ir >> 5) & 0x1f; //r2, 5 bits
    int operand = (ir >> 10) & 0x3f; //operand , 6 bits
    int rm = (ir >> 16) & 0x1f; //r1, 5 bits
    int opr = (ir >> 21) & 0xf; //determines type of dpi w m, 4 bits
    int m = (ir >> 28) & 0x1; //'', 1 bit
    int opc = (ir >> 29) & 0x3; //opcode, determines op, 2 bits
    int sf = ir >> 31; //1 bit, 0=32 bit regs, 1=64 bit regs

    if (m == 0){
        int shift = (opr >> 1) & 0x3;
        int op2 = p.genregs[rm];
        if (sf == 0) {
            op2 = op2 & 0xffffffff;
        }
        switch (shift) {
                case 0:
                    //lsl
                    op2 = op2 << operand
                case 1:
                    //lsr
                    op2 = op2 >> operand
                case 2:
                    //asr
                    
                case 3:
                    if (opr < 8) {
                    //ror
                    }
            }
        if ((opr & 0x1) == 1) {
        // negate that b
        }


// below is questionable
        if (((opr & 0x1) == 0) && (((opr >> 3) & 0x1) == 1)) {
        //arithmetic
        }
        else if (opr < 8) {
        //bit-logic
            
        }
    }
    else if ((m == 1) && (opr == 8)){
    //multiply
    }


}
