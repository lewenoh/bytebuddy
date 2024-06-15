#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "split_lines.h"
#include "table_def.h"
#define LINE_CAPACITY 10

char **split_lines(FILE *inputFile, char *lineBuffer, int *instrCount) {
	if (fseek(inputFile, 0, SEEK_END) == -1) {
                fclose(inputFile);
                fprintf(stderr, "Error seeking to end of file.\n");
                abort(); // seek failure
        }

        // now at end of file
        long fileSize = ftell(inputFile); // in bytes
        int numChar = fileSize / sizeof(char);
        rewind(inputFile); // return to start

	lineBuffer = malloc(fileSize + 1); // allocating suitable amount of space in lineBuffer.

        assert(lineBuffer != NULL);

	int charsRead = fread(lineBuffer, sizeof(char), numChar, inputFile); // reading from inputFile to lineBuffer

        if (charsRead < numChar) { // verifying that read was successful
                fclose(inputFile);
		free(lineBuffer);
                fprintf(stderr, "Error reading from file.\n");
		exit(1);
	}

	lineBuffer[charsRead] = '\0'; // null terminating the buffer

	// processing chars in lineBuffer to split line by line.

	char **instrLines = malloc(LINE_CAPACITY * sizeof(char *)); // allocating a suitable amount of space in 2D array instrLines.

	assert(instrLines != NULL);

	size_t instrLineIndex = 0;

    	char *line = strtok(lineBuffer, "\n"); // split the buffer into lines

	while (line != NULL) {
		//instrLines[instrLineIndex] = malloc(sizeof(char *)); // Allocate memory for each line
        	instrLines[instrLineIndex] = (char *) malloc(strlen(line) + 1);
		if (instrLines[instrLineIndex] == NULL) {
            		perror("Error allocating memory");

			for (int i = 0; i < instrLineIndex; i++) {
                		free(instrLines[i]);
            		}
            		free(lineBuffer);
            		free(instrLines);
            		fclose(inputFile);
			exit(1);

        	}
		//instrLines[instrLineIndex] = realloc(instrLines[instrLineIndex], sizeof(*instrLines[instrLineIndex]) + strlen(line));
        	strcpy(instrLines[instrLineIndex], line); // Copy the line into the array
		*instrCount = *instrCount + 1;
        	instrLineIndex++;
        	line = strtok(NULL, "\n"); // get the next line
    	}

	if (ferror(inputFile)) {
 	       perror("Error reading file");
    	}

    	// Free the allocated memory
	free(lineBuffer);

    	fclose(inputFile);
    	return instrLines;
}

//	while (count < numChar) {
//		char *currLine; // do i need to malloc here or can i realloc with no data
//		size_t currLength;
//
//		while (lineBuffer[count] != '\n') { // new line reached
//			currLength = (currLine == NULL) ? 0 : strlen(currLine); // check that currString has enough of space
//			currLine = (char *)(realloc(currLine, currLength + 1)); // reallocate to include new char
//			currLine[currLength] = lineBuffer[count];
//			count++;
//		}
//
//		instrLines = (char **)realloc(instrLines, (instrLineIndex + 1) * sizeof(char *));
//
//		currLength = (currLine == NULL) ? 0 : strlen(currLine);
//		currLine = (char *)(realloc(currLine, currLength + 1));
//		currLine[currLength] = '\0'; // terminating character for the last element of each line.
//
//		instrLines[instrLineIndex] = currLine;
//
//		free(currLine);
//
//		count++;
//
//		instrLineIndex++;

