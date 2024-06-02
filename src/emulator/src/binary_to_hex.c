#include <stdlib.h>
#include <stdio.h>
#include "binary_to_hex.h"

uint32_t binaryToHex(uint32_t binaryValue) {
    uint32_t hexValue = 0;

    // Convert each group of 4 bits to hexadecimal
    for (int i = 0; i < 8; i++) {
        uint32_t nibble = (binaryValue >> (4 * i)) & 0xF; // Extract 4 bits at a time
        uint32_t hexDigit = (nibble < 10) ? ('0' + nibble) : ('A' + nibble - 10);
        hexValue |= hexDigit << (4 * (8 - i)); // Place the hex digit in the appropriate position
    }

    return hexValue;
}
