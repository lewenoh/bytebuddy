#ifndef HELPERFUNCS_H
#define HELPERFUNCS_H

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

uint32_t readimm(char imm[30]);
uint32_t getreg(char reg[30]);
bool not_label_int(char * buffer);
bool is_dpi(char * buffer);
bool is_branch(char * buffer);
bool is_sdt(char * buffer);
bool is_special(char * buffer);
#endif
