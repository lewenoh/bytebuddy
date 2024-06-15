#ifndef TABLE_DEF_H
#define TABLE_DEF_H

// We would have to implement the array of pointers to strings dynamically ourselves.
// #define NUMBER_OF_INSTRUCTIONS 1

extern char *instruction_table[50];
// This will have to change. Should be an array of symbol_table.
//extern struct label_entry symbol_table[1];
//typedef char* tokenised_string[5][30];
////extern char tokenised[50][5][30];

#define MAX_ARGS 6
#define MAX_ARG_LENGTH 30
#define NULL_CHAR '\0'
typedef char token_arr[MAX_ARGS][MAX_ARG_LENGTH];
typedef char * instruction;
//#define LINE_CAPACITY 10
//typedef char instruction[MAX_LINE_CAP];
//typedef char instruction[LINE_CAPACITY];
typedef int index;
typedef char * instruction;
typedef struct {
    int size;
    instruction * instructions;
} instruction_array;
typedef instruction * instructionLinesType;
struct label_entry {
    char *label;
    int address;
};
extern char tokenised[50][5][30];
#endif 
