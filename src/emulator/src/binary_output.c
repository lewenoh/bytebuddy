#include <stdio.h>
#include <stdlib.h>
#include "binary_output.h"
#include "processor_def.h"

int binary_output(struct processor *p, FILE *outputFile) {

// processor struct (uint64_t genregs[31]; uint64_t pc; bool pstate[4]; uint32_t memory[524288];)
	char printBuffer[100];

	// writing genreg values

	for (int i = 0; i < 32; i++) {
		int charsWritten = snprintf(printBuffer, sizeof(printBuffer), "X%02d = %016llx\n", i, (*p).genregs[i]);
		if (charsWritten < 0 || charsWritten > 24) { // 24 chars including null terminator and \n
			fprintf(stderr, "Error formatting string for register X%02d\n", i);
			continue;
		}
		fwrite(printBuffer, sizeof(char), charsWritten, outputFile); // write formatted string from pB into output file

		for (int x = 0; x < 100; x++) {
			printBuffer[x] = '\0'; // clearing printBuffer after every iteration
		}
	}

	//////////////////////////////////

	// writing PC value

	int charsWrittenPC = snprintf(printBuffer, sizeof(printBuffer), "PC = %016llx\n", (*p).pc);
                if (charsWrittenPC < 0 || charsWrittenPC > 23) { // 23 chars including null terminator and \n
                        fprintf(stderr, "Error formatting string for PC");
                        continue;
                }
                fwrite(printBuffer, sizeof(char), charsWrittenPC, outputFile); // write formatted string from pB into output file

	fwrite(printBuffer, sizeof(char), chardWrittenPC, outputFile); // writing PC value

	for (int x = 0; x < 100; x++) {
                        printBuffer[x] = '\0'; // clearing printBuffer
                }

	////////////////////////////////////////////////////////////

	// writing PSTATE values

	char flags[5] = {'\0','\0','\0','\0','\0'};

	if ((*p).pstate[0] == true) { flags[0] = 'N' } else { flags[0] = '-' }

	if ((*p).pstate[1] == true) { flags[1] = 'Z' } else { flags[1] = '-' }

	if ((*p).pstate[2] == true) { flags[2] = 'C' } else { flags[2] = '-' }

	if ((*p).pstate[3] == true) { flags[3] = 'V' } else { flags[3] = '-' }

	int charsWrittenPSTATE = snprintf(printBuffer, sizeof(printBuffer), "PSTATE : %s\n", flags);
                if (charsWrittenPSTATE < 0 || charsWrittenPSTATE > 15) { // 15 chars including null terminator and \n
                        fprintf(stderr, "Error formatting string for PSTATE");
                        continue;
                }
                fwrite(printBuffer, sizeof(char), charsWrittenPSTATE, outputFile); // writing PSTATE                                                                                                                                         fwrite(printBuffer, sizeof(char), chardWrittenPC, outputFile); // writing PC value

        for (int x = 0; x < 100; x++) {
                        printBuffer[x] = '\0'; // clearing printBuffer
                }

	/////////////////////////////////////////////////

	// writing non-zero memory

	snprintf(printBuffer, sizeof(printBuffer), "Non-zero memory: \n"); // printing header


	int index = 0

	while (index < 524288) {

		if ((*p).memory[index] != 0x0) {
			// then format to address(convert index*4 to hex) : data
			// then snprintf to printbuffer
			// then fwrite
