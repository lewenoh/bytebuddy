//
// Created by js5422 on 13/06/24.
//

#include "../include/symbol_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//     label_entry *empty_arr = (label_entry *)malloc(sizeof(label_entry) * 0);
//     s->entriesArr = empty_arr;

label_entry *create_entry(char * label, char * address) {
//    strcpy(p_label, label);
//    strcpy(p_address, address);
    label_entry *p_le = (label_entry*) malloc(sizeof(label_entry));
    strcpy(p_le->label, label);
    strcpy(p_le->address, address);
    return p_le;
}


symbol_table *create_symbol_table() {
    label_entry *labelEntry = create_entry("next", "0x8");
    label_entry *labelEntry1 = create_entry("chiat", "0x4");
    symbol_table *s = (symbol_table*) malloc(sizeof(symbol_table));
    if (s == NULL) {
        abort();
    }

    s ->size = 2;
    label_entry **entry_arr = (label_entry **)malloc(sizeof(label_entry *) * s->size);
    if (entry_arr == NULL) {
        abort();
    }
    entry_arr[0] = labelEntry;
    entry_arr[1] = labelEntry1;
    s->entriesArr = entry_arr;
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
    symbol_table *sym = create_symbol_table();
    free_symbol_table(sym);
}


void test_symbol() {
    symbol_table *sym = create_symbol_table();
    address test1;
    char label_test[] = "hm";
    test1 = get_address(*sym, label_test);
    printf("Result: %s\n", test1);
    free_symbol_table(sym);

}


