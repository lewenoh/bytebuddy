#include <stdio.h>
#include <stdlib.h>
#include "binary_output.h"
#include "processor_def.h"
#define BUFFER_SIZE 100
#define TOTAL_GEN_REGS 32
#define REG_HEADING_CHARS 11
#define REG_CHARS 27
#define PSTATE_CHARS 16
#define NON_ZERO_HEADING_CHARS 17
#define NON_ZERO_MEM_CHARS 22
#define MEMORY_SIZE 524288

void clearBuffer(char buffer[], size_t size) {
	for (int x = 0; x < size; x++) {
		buffer[x] = '\0'; // clearing printBuffer
	}
}

int binary_output(struct processor *p, FILE *outputFile) {

// processor struct (uint64_t genregs[31]; uint64_t pc; bool pstate[4]; uint32_t memory[524288];)
	char printBuffer[BUFFER_SIZE];

	// writing genreg values

	snprintf(printBuffer, sizeof(printBuffer), "Registers:\n"); // printing header
        fwrite(printBuffer, sizeof(char), REG_HEADING_CHARS, outputFile); // including \n
        clearBuffer(printBuffer, BUFFER_SIZE);

	for (int i = 0; i < TOTAL_GEN_REGS - 1; i++) {
		int charsWritten = snprintf(printBuffer, sizeof(printBuffer), "X%02d    = %016lx\n", i, (*p).genregs[i]);
		if (charsWritten < 0 || charsWritten > REG_CHARS) { // 27 chars including null terminator and \n
			fprintf(stderr, "Error formatting string for register X%02d\n", i);
			continue;
		}
		fwrite(printBuffer, sizeof(char), charsWritten, outputFile); // write formatted string from pB into output file

		clearBuffer(printBuffer, BUFFER_SIZE);
	}

	//////////////////////////////////

	// writing PC value

	int charsWrittenPC = snprintf(printBuffer, sizeof(printBuffer), "PC     = %016lx\n", (*p).pc);
                if (charsWrittenPC < 0 || charsWrittenPC > REG_CHARS) { // 27 chars including null terminator and \n
                        fprintf(stderr, "Error formatting string for PC\n");
		}

		fwrite(printBuffer, sizeof(char), charsWrittenPC, outputFile); // writing PC value

		clearBuffer(printBuffer, BUFFER_SIZE);

	////////////////////////////////////////////////////////////

	// writing PSTATE values

	char flags[5] = {'\0','\0','\0','\0','\0'};

	if ((*p).pstate[0] == true) { flags[0] = 'N'; } else { flags[0] = '-'; }

	if ((*p).pstate[1] == true) { flags[1] = 'Z'; } else { flags[1] = '-'; }

	if ((*p).pstate[2] == true) { flags[2] = 'C'; } else { flags[2] = '-'; }

	if ((*p).pstate[3] == true) { flags[3] = 'V'; } else { flags[3] = '-'; }

	int charsWrittenPSTATE = snprintf(printBuffer, sizeof(printBuffer), "PSTATE : %s\n", flags);
                if (charsWrittenPSTATE < 0 || charsWrittenPSTATE > PSTATE_CHARS) { // 16 chars including null terminator and \n
                        fprintf(stderr, "Error formatting string for PSTATE\n");
                }
                fwrite(printBuffer, sizeof(char), charsWrittenPSTATE, outputFile); // writing PSTATE                                                                                                                                         fwrite(printBuffer, sizeof(char), chardWrittenPC, outputFile); // writing PC value

        clearBuffer(printBuffer, BUFFER_SIZE);

	/////////////////////////////////////////////////

	// writing non-zero memory

	snprintf(printBuffer, sizeof(printBuffer), "Non-Zero Memory:\n"); // printing header
	fwrite(printBuffer, sizeof(char), NON_ZERO_HEADING_CHARS, outputFile); // including \n
	clearBuffer(printBuffer, BUFFER_SIZE);

	int index = 0;

	while (index < MEMORY_SIZE) {

		if ((*p).memory[index] != 0x0) { // if memory is non-null
			int charsWrittenMem = snprintf(printBuffer, sizeof(printBuffer), "0x%08x : %08x\n", (unsigned int)(index*4), (*p).memory[index]);
			if (charsWrittenMem < 0 || charsWrittenMem > NON_ZERO_MEM_CHARS) { // 22 chars including null terminator and \n
				fprintf(stderr, "Error formatting string for memory address 0x%08x\n", (unsigned int)(index*4));
				continue;
			}

			fwrite(printBuffer, sizeof(char), charsWrittenMem, outputFile); // write formatted string from pB into output file

			clearBuffer(printBuffer, BUFFER_SIZE);
		}

		index++; // move to the next memory location
	}

	return 0;

}
