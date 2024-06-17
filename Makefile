CC = gcc
CFLAGS = -Wall
SRC_DIR = src/
BUILD = armv8_51

all:
	+$(MAKE) -C $(SRC_DIR)/assembler
	+$(MAKE) -C $(SRC_DIR)/emulator

clean:
	+$(MAKE) -C $(SRC_DIR)/assembler clean
	+$(MAKE) -C $(SRC_DIR)/emulator clean
