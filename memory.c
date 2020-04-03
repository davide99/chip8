#include "memory.h"
#include <stdlib.h>
#include <stdio.h>

#define ROM_LOAD_OFFSET 0x200

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

void memCopyROMFromFile(Memory mem, const char *filename) {
    FILE *f;
    size_t size;

    if ((f = fopen(filename, "rb")) != NULL) {
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        rewind(f);

        fread(mem.data + ROM_LOAD_OFFSET, sizeof(uint8_t), size, f);

        fclose(f);
    }
}
