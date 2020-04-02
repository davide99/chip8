#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H

#include "cpu.h"
#include "memory.h"
#include "display.h"

typedef struct {
    CPU cpu;
    Memory memory;
    Display display;
} CHIP8;

CHIP8 chip8Init();

#endif
