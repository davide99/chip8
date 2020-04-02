#include "cpu.h"
#include "chip8.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

#define V_REGISTERS 16
#define ONE_OVER_60_MS 1000.0/60

struct CPU_s {
    struct {
        uint8_t VX[V_REGISTERS]; //V0~VF registers
        uint16_t I;
        uint8_t DT, ST; //delay timer register, sound timer register
    } regs;

    struct {
        uint16_t PC; //Program Counter
        uint8_t SP; //Stack Pointer
        uint16_t stack[16]; //Chip8 define a stack of exactly 16
    } __internal;

    CHIP8 chip8;
};

static int DTthread(void *ptr) {
    CPU cpu = ptr;

    while (cpu->regs.DT > 0) {
        cpu->regs.DT--;
        SDL_Delay(ONE_OVER_60_MS);
    }

    return 0;
}

static int STthread(void *ptr) {
    CPU cpu = ptr;

    while (cpu->regs.ST > 0) {
        cpu->regs.ST--;
        //TODO: beep
        SDL_Delay(ONE_OVER_60_MS);
    }

    return 0;
}

CPU cpuInit(CHIP8 chip8) {
    CPU cpu = malloc(sizeof(struct CPU_s));
    cpu->chip8 = chip8;
    cpu->regs.ST = cpu->regs.DT = 0;

    return cpu;
}

uint8_t cpuGetByteRegister(CPU cpu, enum Register r) {
    if (r >= V0 && r <= VF)
        return cpu->regs.VX[r];
    else if (r == DT)
        return cpu->regs.DT;
    else if (r == ST)
        return cpu->regs.ST;

    return 0;
}

void cpuSetByteRegister(CPU cpu, enum Register r, uint8_t value) {
    if (r >= V0 && r <= VF) {
        cpu->regs.VX[r] = value;
    } else if (r == DT) {
        cpu->regs.DT = value;
        SDL_DetachThread(SDL_CreateThread(DTthread, "DTthread", cpu));
    } else if (r == ST) {
        cpu->regs.ST = value;
        SDL_DetachThread(SDL_CreateThread(STthread, "STthread", cpu));
    }
}

uint16_t cpuGetIRegister(CPU cpu) {
    return cpu->regs.I;
}

void cpuSetIRegister(CPU cpu, uint16_t value) {
    cpu->regs.I = value;
}

void cpuStart(CPU cpu) {
    
}