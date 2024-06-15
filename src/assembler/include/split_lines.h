#ifndef SPLIT_LINES_H
#define SPLIT_LINES_H
#include "table_def.h"
#include "instruction_arr.h"

void split_lines(FILE *inputFile, instruction_array *ia,char *lineBuffer);
void initial_processing(FILE *inputFile, long *fileSize, int * numChar);
void read_whole_file(char * lineBuffer, int numChar, FILE *inputFile);
void test_ilines();
#endif
