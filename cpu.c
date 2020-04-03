#include "cpu.h"
#include <SDL2/SDL.h>

#define ONE_OVER_60_MS 1000.0/60
#define PC_START_ADDR 0x200

int DTthread(void *ptr) {
    CPU *cpu = ptr;

    while (cpu->regs.DT > 0) {
        cpu->regs.DT--;
        SDL_Delay(ONE_OVER_60_MS);
    }

    return 0;
}

int STthread(void *ptr) {
    CPU *cpu = ptr;

    while (cpu->regs.ST > 0) {
        cpu->regs.ST--;
        //TODO: beep
        SDL_Delay(ONE_OVER_60_MS);
    }

    return 0;
}

CPU cpuInit() {
    CPU cpu = {
            .regs = {
                    .ST=0,
                    .DT=0,
                    .PC = PC_START_ADDR,
            },
    };
    return cpu;
}