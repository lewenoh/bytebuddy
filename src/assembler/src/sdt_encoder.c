#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "helperfuncs.h"
#include "sdt_encoder.h"

#define SF64SET 0x40000000 //sf bit set to 1 when 64 bit regs (x)
#define LLBASE 0x18000000 //base for load literal instructions
#define UNSIGNEDU 0x1000000 //U bit set for unsigned offset
#define LOADLBIT 0x400000 //L bit set for load operations
#define SDTBASE 0xb8000000 //base for sdt instructions
#define ROBASE 0x206800 //base for register offsets
#define PREBASE 0xc00 //base for pre index
#define POSTBASE 0x400 //base for post index
#define SIMMMASK 0x1ff //mask for simm9 
#define SIMM19MASK 0x7ffff //mask for simm19

uint32_t sdt_encoder(uint32_t address, char instruction[6][30]){
	//opcode = i[0], rt = i[1], xn/literal = i[2], type = i[5]
	uint32_t hexi = 0;
	unsigned int regsize = 0; //for 32 bit
	if (instruction[1][0] == 'x'){
		hexi = SF64SET;
		regsize = 1; //64 bit reg
	}
	hexi = hexi + getreg(instruction[1]);
	
	if ((instruction[2][0] != 'w') || (instruction[2][0] != 'x')){
		//load literal
		hexi = hexi + LLBASE;
		hexi = hexi + ((((readimm(instruction[2]) - address) / 4) & SIMM19MASK) << 5); //simm19
	}
	else {
		//sdt
		//xn = i[2] 
		hexi = hexi + SDTBASE + (getreg(instruction[2]) << 5);
		if (strcmp(instruction[5], "U")==0){//unsigned offset
			hexi = hexi + UNSIGNEDU;
			if (instruction[3][0] != '\0'){
				//not zero unsigned offset
				uint32_t imm12 = readimm(instruction[3])/4;
				if (regsize>0){
					imm12 = imm12/2;	
				}
				hexi = hexi + (imm12 << 10);
			}
		
		}
		else if (strcmp(instruction[5], "PRE")==0){
			hexi = hexi + PREBASE + ((readimm(instruction[3])&SIMMMASK) <<12);
		}
		else  if (strcmp(instruction[5], "POST")==0){ 
			hexi = hexi + POSTBASE + ((readimm(instruction[3])&SIMMMASK) <<12);
		}
		else {	//N, register offset
			hexi = hexi + ROBASE + (getreg(instruction[3]) << 16);
		}

		//L bit
		if (strcmp(instruction[0], "ldr")==0){
			hexi = hexi + LOADLBIT;
		}

	}


	return hexi;
}
