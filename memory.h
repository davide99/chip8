#ifndef CHIP8_MEMORY_H
#define CHIP8_MEMORY_H

#include <stdint.h>

#define MEM_SIZE 4096
#define ROM_LOAD_OFFSET 0x200

typedef struct {
    uint8_t *data;
    uint16_t size;
} Memory;

Memory memInit();

uint16_t memReadWord(Memory mem, uint16_t address);

void memCopyROMFromFile(Memory mem, const char *filename);

void memFree(Memory mem);

#endif
