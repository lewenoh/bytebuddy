#include <stdlib.h>
#include <stdio.h>
#include "split_lines.h"
#include "table_def.h"

// TODO remember to free malloced, double-check all code

char **split_lines(FILE *inputFile, char *lineBuffer) {
	if (fseek(inputFile, 0, SEEK_END) == -1) {
                fclose(inputFile);
                fprintf(stderr, "Error seeking to end of file.\n");
                return 1; // seek failure
        }

        // now at end of file
        long fileSize = ftell(inputFile); // in bytes
        int numChar = fileSize / sizeof(char);
        rewind(inputFile); // return to start

	lineBuffer = malloc(fileSize); // allocating suitable amount of space in lineBuffer.

        int charsRead = fread(lineBuffer, sizeof(char), numChar, inputFile); // reading from inputFile to lineBuffer

        if (charsRead < numChar) { // verifying that read was successful
                fclose(inputFile);
                fprintf(stderr, "Error reading from file.\n");
		exit(1);
	}

	// processing chars in lineBuffer to split line by line.

	char **instrLines; // allocating a suitable amount of space in 2D array instrLines.

	size_t instrLineIndex = 0;
	int count = 0;

	while (count < numChar) {
		char *currLine; // do i need to malloc here or can i realloc with no data
		size_t currLength;

		while (lineBuffer[count] != '\n') { // new line reached
			currLength = (currLine == NULL) ? 0 : strlen(currLine); // check that currString has enough of space
			currLine = (char *)(realloc(currLine, currLength + 1)); // reallocate to include new char
			currLine[currLength] = lineBuffer[count];
			count++;
		}

		instrLines = (char **)realloc(instrLines, (instrLineIndex + 1) * sizeof(char *));

		currLength = (currLine == NULL) ? 0 : strlen(currLine);
		currLine = (char *)(realloc(currLine, currLength + 1));
		currLine[currLength] = '\0'; // terminating character for the last element of each line.

		instrLines[instrLineIndex] = currLine;

		free(currLine);

		count++;

		instrLineIndex++;
	}

	return instrLines;

}
