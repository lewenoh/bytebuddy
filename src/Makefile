CC      ?= gcc
CFLAGS  ?= -std=c17 -g\
	-D_POSIX_SOURCE -D_DEFAULT_SOURCE\
	-Wall -Werror -pedantic

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate

sdt.o: sdt.c sdt.h ProcessorDef.h
dpiReg.o: dpiReg.c dpiReg.h ProcessorDef.h
dpiImm.o: dpiImm.c dpiImm.h ProcessorDef.h
decoder.o: decoder.c decoder.h ProcessorDef.h
branch.o: branch.c branch.h ProcessorDef.h
emulate.o: ProcessorDef.h emulate.c

assemble: assemble.o
emulate: emulate.o



clean:
	$(RM) *.o assemble emulate
	
