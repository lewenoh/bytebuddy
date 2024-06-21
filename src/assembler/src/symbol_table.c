//
// Created by js5422 on 13/06/24.
//

#include "../include/symbol_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

label_entry *create_entry(char * label, char * address) {
    label_entry *p_le = (label_entry*) malloc(sizeof(label_entry));
    strcpy(p_le->label, label);
    strcpy(p_le->address, address);
    return p_le;
}

symbol_table *create_empty_table() {
    symbol_table *s = (symbol_table*) malloc(sizeof(symbol_table));
    if (s == NULL) {
        abort();
    }
    s->size = 0;
    s->entriesArr = NULL;
    return s;
}

void add_entry(symbol_table *symbolTable, label_entry *labelEntry) {
    label_entry **entry_arr = (label_entry **)realloc(symbolTable->entriesArr,
                                                      sizeof(label_entry *) * (symbolTable->size+1));
    if (entry_arr == NULL) {
        abort();
    }
    symbolTable->entriesArr = entry_arr;
    entry_arr[symbolTable->size] = labelEntry;
    symbolTable->size ++;
}


symbol_table *create_example_symbol_table() {
    symbol_table *s = create_empty_table();
    label_entry *labelEntry = create_entry("next", "0x8");
    add_entry(s, labelEntry);
    label_entry *labelEntry1 = create_entry("chiat", "0x4");
    add_entry(s, labelEntry1);
    return s;
}

void free_symbol_table(symbol_table *s) {
    for (int i = 0; i < s->size; i++) {
        free(s->entriesArr[i]);
    }
    free(s->entriesArr);
    free(s);
}

address get_address(symbol_table sym, char * label) {
    // Iterate through symbol table.
    for (int i = 0; i < sym.size; i++) {
        char * curr_label = sym.entriesArr[i]->label;
        if (strcmp(curr_label, label) == 0) {
            return sym.entriesArr[i]->address;
        }
    }
    return NULL;
}

void test_create_symbol() {
    symbol_table *sym = create_example_symbol_table();
    free_symbol_table(sym);
}


void test_get_address() {
    symbol_table *sym = create_example_symbol_table();
    address test1;
    char label_test[] = "hm";
    test1 = get_address(*sym, label_test);
    printf("Result: %s\n", test1);
    free_symbol_table(sym);

}


