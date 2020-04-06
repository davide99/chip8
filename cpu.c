#include "cpu.h"
#include <SDL2/SDL.h>

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
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;

    SDL_LoadWAV("beep.wav", &wavSpec, &wavBuffer, &wavLength);

    while (cpu->regs.ST > 0) {
        cpu->regs.ST--;
        SDL_Delay(ONE_OVER_60_MS);
    }

    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);

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