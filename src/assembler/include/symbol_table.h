//
// Created by js5422 on 13/06/24.
//

#ifndef ARMV8_51_SYMBOL_TABLE_H
#define ARMV8_51_SYMBOL_TABLE_H
#include "table_def.h"
#define MAX_ENTRY_ARG_LEN 100
typedef struct {
    char label[MAX_ENTRY_ARG_LEN];
    char address[MAX_ENTRY_ARG_LEN];
} label_entry;

typedef struct {
    int size;
    label_entry **entriesArr;
} symbol_table;
symbol_table *create_symbol_table();
void test_symbol();
void test_create_symbol();
typedef char * address;

#endif //ARMV8_51_SYMBOL_TABLE_H
