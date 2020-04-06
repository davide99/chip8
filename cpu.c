#include "cpu.h"
#include <SDL2/SDL.h>

#ifdef WIN32

#include <windows.h>

#endif

#define ONE_OVER_60_MS 1000.0/60

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
        SDL_Delay(ONE_OVER_60_MS);
    }

#ifdef WIN32
    Beep(440, 1000);
#endif

    return 0;
}

CPU cpuInit(uint16_t startingAddress) {
    CPU cpu = {
            .regs = {
                    .ST=0,
                    .DT=0,
                    .PC = startingAddress,
                    .I =0,
                    .SP=0
            },
    };
    return cpu;
}