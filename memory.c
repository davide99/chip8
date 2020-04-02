#include "memory.h"
#include <stdlib.h>

Memory memInit() {
    Memory memory = {
            .data = malloc(sizeof(uint8_t) * MEM_SIZE),
            .size = MEM_SIZE
    };

    return memory;
}

uint16_t memReadWord(Memory mem, uint16_t address) {
    //CHIP8 is Big Endian
    return mem.data[address] << 8u | mem.data[address + 1];
}

void memFree(Memory mem) {
    free(mem.data);
}