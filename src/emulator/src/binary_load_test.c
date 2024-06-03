#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "binary_load.h"
#include "processor_def.h"
#include "testcond.h"

void binary_load_test() {
	struct processor p = {{0x0}, 0x0, {false, true, false, false}, {0x0}}; // initialise processor

	uint32_t data[] = {0x12345678, 0xabcdef00, 0xdeadbeef} ;

	// {0x12345678, 0xabcdef00, 0xdeadbeef}

    	// Open a binary file for writing
    	FILE *writeFile = fopen("test.bin", "wb");

	fwrite(data, sizeof(uint32_t), 3, writeFile);

	fclose(writeFile);

	FILE *readFile = fopen("test.bin", "rb");

	binary_load(&p, readFile);

	fclose(readFile); 

	for (int i = 0; i < 3; i++) {
		printf("Memory[%d]: 0x%08x\n", i, p.memory[i]);
	}
}
