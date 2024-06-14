#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, char **argv) {
  // .s file read -> Instruction table, Symbol Table
  // For each instruction, classify.
  // Encode each instruction into binary.
  // Write binary to .bin file. 
  
	int noinstrs = 4;
	uint32_t instrs[noinstrs];
	instrs[0] = 0x14000002;
 	instrs[1] = 0x91003000;
	instrs[2] = 0x91000400;
	instrs[3] = 0x8a000000;	
	//uint32_t instr = 0;
	//for (int x=0; x < noinstrs; x++){
	//in for loop: decode and encode each instruction
	//	instr = encodefunc(instruction);
	//	instrs[x] = instr;
	//}




	//after for loop
	FILE *outputfile = fopen(argv[1], "wb");
	if (outputfile == NULL || ferror(outputfile)){
		fprintf(stderr, "Error opening output file.\n");
		exit(1);
	}
	
	int instrwrite = fwrite(instrs, 4, noinstrs, outputfile);
	if (instrwrite < noinstrs){
		fclose(outputfile);
		fprintf(stderr, "Error writing to the file.\n");
	}
	fclose(outputfile);


	return EXIT_SUCCESS;
}
