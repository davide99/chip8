#include "cpu.h"
#include <SDL2/SDL.h>

#define ONE_OVER_60_MS 1000.0/60
#define PC_START_ADDR 0x200

static int DTthread(void *ptr) {
    CPU *cpu = ptr;

    while (cpu->regs.DT > 0) {
        cpu->regs.DT--;
        SDL_Delay(ONE_OVER_60_MS);
    }

    return 0;
}

static int STthread(void *ptr) {
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

    //TODO: SDL_DetachThread(SDL_CreateThread(DTthread, "DTthread", cpu));
    //TODO: SDL_DetachThread(SDL_CreateThread(STthread, "STthread", cpu));

    return cpu;
}