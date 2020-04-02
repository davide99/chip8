#include "chip8.h"
#include "cpu.h"
#include "memory.h"
#include "display.h"
#include <stdlib.h>
#include <stdint.h>

struct CHIP8_s {
    CPU cpu;
    Memory memory;
    Display display;
};

static void _execute(CHIP8 chip8) {
    uint16_t opcode;

    opcode = memReadWord(chip8->memory, chip8->cpu.regs.PC);

    switch (opcode >> 12u) { //MSB
        case 0x0:
            switch (opcode & 0xFFFu) {
                case 0x0E0: //CLS: display clear
                    dispClear(chip8->display);
                    break;

                case 0x0EE: //RET: return from a subroutine
                    //TODO: implementare
                    break;
            }
            break;

        case 0x1: //JP: jump
            chip8->cpu.regs.PC = opcode & 0xFFFu;
            break;

    }


}

CHIP8 chip8Init() {
    CHIP8 chip8 = malloc(sizeof(struct CHIP8_s));

    chip8->cpu = cpuInit();
    chip8->memory = memInit();
    chip8->display = dispInit();

    _execute(chip8);

    return chip8;
}

void chip8Free(CHIP8 chip8) {
    free(chip8);
}
