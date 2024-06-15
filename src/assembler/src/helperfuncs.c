#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "../include/helperfuncs.h"

bool is_dpi(char * buffer) {
    return strcmp(buffer, "add")==0 ||
        strcmp(buffer, "adds")==0 ||
        strcmp(buffer, "sub") == 0 ||
        strcmp(buffer, "subs")==0 ||
        strcmp(buffer, "cmp") == 0 ||
        strcmp(buffer, "cmn") == 0 ||
        strcmp(buffer, "neg") == 0 ||
        strcmp(buffer, "negs") == 0 ||
        strcmp(buffer, "and")==0 ||
        strcmp(buffer, "ands")==0 ||
        strcmp(buffer, "bic")==0 ||
        strcmp(buffer, "bics")==0 ||
        strcmp(buffer, "eor")==0 ||
        strcmp(buffer, "orr")==0 ||
        strcmp(buffer, "eon")==0 ||
        strcmp(buffer, "orn")==0 ||
        strcmp(buffer, "tst") == 0 ||
        strcmp(buffer, "movk") == 0 ||
        strcmp(buffer, "movn") == 0 ||
        strcmp(buffer, "movz") == 0 ||
        strcmp(buffer, "mov") == 0 ||
        strcmp(buffer, "mvn") == 0 ||
        strcmp(buffer, "madd") == 0 ||
        strcmp(buffer, "msub") == 0 ||
        strcmp(buffer, "mul") == 0 ||
        strcmp(buffer, "mneg") == 0;
}

bool is_branch(char * buffer) {
    return strcmp(buffer, "br") == 0 ||
    strcmp(buffer, "b") == 0 ||
    strcmp(buffer, "b.eq") == 0 ||
    strcmp(buffer, "b.ne") == 0 ||
    strcmp(buffer, "b.ge") == 0 ||
    strcmp(buffer, "b.lt") == 0 ||
    strcmp(buffer, "b.gt") == 0 ||
    strcmp(buffer, "b.le") == 0 ||
    strcmp(buffer, "b.al") == 0;
}

bool is_sdt(char * buffer) {
    return strcmp(buffer, "ldr") == 0 ||
    strcmp(buffer, "str")==0;
}

bool is_special(char * buffer) {
    return strcmp(buffer, ".int") == 0;
}

bool not_label_int(char * buffer) {
     return strcmp(buffer, "cmp") == 0 ||
            strcmp(buffer, "cmn") == 0 ||
            strcmp(buffer, "neg") == 0 ||
            strcmp(buffer, "negs") == 0 ||
            strcmp(buffer, "tst") == 0 ||
            strcmp(buffer, "movk") == 0 ||
            strcmp(buffer, "movn") == 0 ||
            strcmp(buffer, "movz") == 0 ||
            strcmp(buffer, "mov") == 0 ||
            strcmp(buffer, "mvn") == 0 ||
            strcmp(buffer, "madd") == 0 ||
            strcmp(buffer, "msub") == 0 ||
            strcmp(buffer, ".int") == 0 ||
            strcmp(buffer, "br") == 0 ||
            strcmp(buffer, "b") == 0 ||
            strcmp(buffer, "b.eq") == 0 ||
            strcmp(buffer, "b.ne") == 0 ||
            strcmp(buffer, "b.ge") == 0 ||
            strcmp(buffer, "b.lt") == 0 ||
            strcmp(buffer, "b.gt") == 0 ||
            strcmp(buffer, "b.le") == 0 ||
            strcmp(buffer, "b.al") == 0 ||
            strcmp(buffer, "ldr") == 0 ||
            strcmp(buffer, "str")==0 ||
            strcmp(buffer, "add")==0 ||
            strcmp(buffer, "adds")==0 ||
            strcmp(buffer, "sub") == 0 ||
            strcmp(buffer, "subs")==0 ||
            strcmp(buffer, "and")==0 ||
            strcmp(buffer, "ands")==0 ||
            strcmp(buffer, "bic")==0 ||
            strcmp(buffer, "bics")==0 ||
            strcmp(buffer, "eor")==0 ||
            strcmp(buffer, "orr")==0 ||
            strcmp(buffer, "eon")==0 ||
            strcmp(buffer, "orn")==0;
}
uint32_t readimm(char imm[30]){
	//takes a register and returns the hex value encoding for it
	if (imm[0] == '#'){	
		memmove (imm, imm+1, 3);
	}
	uint32_t result;
	if (imm[1] == 'x'){
		//hex
		memmove(imm, imm+2, 27);
		result = strtol(imm, NULL, 16);
	}
	else {
		//decimal
		result = atoi(imm);
	}
	return result;
}

uint32_t getreg(char reg[30]){
	memmove (reg, reg+1, 29);
	return atoi(reg);
}
