#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../include/split_lines.h"
#include "../include/instruction_arr.h"
#define LINE_CAPACITY 10



void test_ilines() {
    instruction_array *ia = create_empty_instructionArr();
    instruction i;
    i = create_instruction("and x0, x0, x0");
    add_instruction(ia, &i);
    free_instruction_arr(ia);
}

void initial_processing(FILE *inputFile, long *fileSize, int * numChar) {
    if (fseek(inputFile, 0, SEEK_END) == -1) {
        fclose(inputFile);
        fprintf(stderr, "Error seeking to end of file.\n");
        abort(); // seek failure
    }

    // now at end of file
    *fileSize = ftell(inputFile); // in bytes
    *numChar = *fileSize / sizeof(char);
    rewind(inputFile); // return to start
}

void read_whole_file(char * lineBuffer, int numChar, FILE *inputFile) {

    // reading from inputFile to lineBuffer
    int charsRead = fread(lineBuffer, sizeof(char), numChar, inputFile);
    if (charsRead < numChar) { // verifying that read was successful
        fclose(inputFile);
        free(lineBuffer);
        fprintf(stderr, "Error reading from file.\n");
        exit(1);
    }
    lineBuffer[charsRead] = '\0'; // null terminating the buffer
}

void split_lines(FILE *inputFile, instruction_array *ia, char *lineBuffer) {
    // LineBuffer contains the entire .s file.
    // Each instruction is separated by \n
    // Write each line to instruction array.

    long fileSize;
    int numChar;
    initial_processing(inputFile, &fileSize, &numChar);
    // allocating suitable amount of space in lineBuffer.
    lineBuffer = (char *) malloc(fileSize + 1);
    assert(lineBuffer != NULL);
    read_whole_file(lineBuffer, numChar, inputFile);
    char *line = strtok(lineBuffer, "\n"); // split the buffer into lines

	while (line != NULL) {
        // Symbol Table logic goes here.
        instruction curr_instruction = create_instruction(line);
        add_instruction(ia, &curr_instruction);
        line = strtok(NULL, "\n"); // get the next line
    	}

	if (ferror(inputFile)) {
 	       perror("Error reading file");
    	}

	free(lineBuffer);
    fclose(inputFile);
}





