#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "ProcessorDef.h"
#define ZEROREG 0x0
#define HALTINSTRUCTION 2315255808

int main(int argc, char **argv) {
  //populating the processor, p
  struct processor p = {{0x0}, 0x0, {false, true, false, false}, {0x0}};
  uint32_t ir = p.memory[p.pc/4];
  //get instruction lines from bin file TODO
  //emulator loop:
  while (ir != HALTINSTRUCTION){
        //fetch:
      ir = p.memory[p.pc/4];
      p.pc += 4;
        //decode and execute: TODO
  }
  //format output TODO
  return EXIT_SUCCESS;
}
