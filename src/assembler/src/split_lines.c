#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../include/split_lines.h"
#define LINE_CAPACITY 10

instruction_array *create_empty_instructionArr() {
    instruction_array *s = (instruction_array *) malloc(sizeof(instruction_array));
    if (s == NULL) {
        abort();
    }
    s->size = 0;
    s->instructions = NULL;
    return s;
}


instruction create_instruction(char * instr) {
    instruction i = (instruction) malloc(sizeof(char) * (strlen(instr)+1));
    assert(i != NULL);
    strcpy(i, instr);
    i[strlen(instr)] = '\0';
    return i;
}

void add_instruction(instruction_array *instructionArray, instruction *instr) {
    instruction *instruction_arr = (instruction *)realloc(instructionArray->instructions,
                                                          sizeof(instruction) * (instructionArray->size+1));
    if (instruction_arr == NULL) {
        abort();
    }
    instructionArray->instructions = instruction_arr;
    instruction_arr[instructionArray->size] = *instr;
    instructionArray->size ++;
}


void free_instruction_arr(instruction_array *instructionArray) {
    for (int i = 0; i < instructionArray->size; i++) {
        free((instructionArray->instructions[i]));
    }
    free(instructionArray->instructions);
    free(instructionArray);
}

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

    long fileSize;
    int numChar;
    initial_processing(inputFile, &fileSize, &numChar);
    // allocating suitable amount of space in lineBuffer.
    lineBuffer = (char *) malloc(fileSize + 1);
    assert(lineBuffer != NULL);
    read_whole_file(lineBuffer, numChar, inputFile);
    char *line = strtok(lineBuffer, "\n"); // split the buffer into lines

	while (line != NULL) {
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

