//
// Created by js5422 on 13/06/24.
//

#ifndef ARMV8_51_SYMBOL_TABLE_H
#define ARMV8_51_SYMBOL_TABLE_H
#include "table_def.h"
#define MAX_ENTRY_ARG_LEN 100
typedef char * address;
typedef struct {
    char label[MAX_ENTRY_ARG_LEN];
    char address[MAX_ENTRY_ARG_LEN];
} label_entry;

typedef struct {
    int size;
    label_entry **entriesArr;
} symbol_table;
symbol_table *create_example_symbol_table();
symbol_table *create_empty_table();
address get_address(symbol_table sym, char * label);
void free_symbol_table(symbol_table *s);
label_entry *create_entry(char * label, char * address);
void add_entry(symbol_table *symbolTable, label_entry *labelEntry);
void test_get_address();
void test_create_symbol();


#endif //ARMV8_51_SYMBOL_TABLE_H
