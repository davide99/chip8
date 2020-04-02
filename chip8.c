#include <fvec.h>
#include "chip8.h"

CHIP8 chip8Init() {
    CHIP8 chip8 = {
            .cpu = cpuInit(result),
            .memory = memInit(),
            .display = dispInit()
    };

    return chip8;
}