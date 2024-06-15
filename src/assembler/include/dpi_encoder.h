#ifndef DPI_ENCODER_H
#define DPI_ENCODER_H

#include <stdint.h>
#include "table_def.h"
#include "tokenise.h"

//uint32_t dpi_encoder(char instruction[6][30]);
uint32_t dpi_encoder(token_arr instruction);

#endif
