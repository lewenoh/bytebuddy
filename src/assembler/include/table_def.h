#ifndef TABLE_DEF_H
#define TABLE_DEF_H

// We would have to implement the array of pointers to strings dynamically ourselves.
// #define NUMBER_OF_INSTRUCIONS 1

extern char *instruction_table[50];

//struct label_entry {
//    char *label;
//    int address;
//};
// This will have to change. Should be an array of symbol_table.
//extern struct label_entry symbol_table[1];
//typedef char* tokenised_string[5][30];
////extern char tokenised[50][5][30];

#define MAX_ARGS 5
#define MAX_ARG_LENGTH 30
typedef char token_arr[MAX_ARGS][MAX_ARG_LENGTH];
typedef char* instruction;
typedef int index;
#endif 
