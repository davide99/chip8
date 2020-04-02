#ifndef CHIP8_MEMORY_H
#define CHIP8_MEMORY_H

#include <stdint.h>

#define MEM_SIZE 4096

typedef struct {
    uint8_t *data;
    uint16_t size;
} Memory;

Memory memInit();

uint16_t memReadWord(Memory mem, uint16_t address);

void memFree(Memory mem);

#endif