#ifndef TABLE_DEF_H
#define TABLE_DEF_H

// We would have to implement the array of pointers to strings dynamically ourselves.
// #define NUMBER_OF_INSTRUCIONS 1

char *instruction_table[50];

struct label_entry {
    char *label;
    int address;
};
struct label_entry symbol_table[1];

char tokenised[50][5][30];
#endif 
