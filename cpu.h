#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

#include <stdint.h>
#include "chip8.h"

enum Register {
    V0 = 0, V1, V2, V3, V4, V5, V6, V7, V8, V9, VA, VB, VC, VD, VE, VF, DT, ST
};

typedef struct CPU_s *CPU;

CPU cpuInit(CHIP8 chip8);

uint8_t cpuGetByteRegister(CPU cpu, enum Register r);

void cpuSetByteRegister(CPU cpu, enum Register r, uint8_t value);

uint16_t cpuGetIRegister(CPU cpu);

void cpuSetIRegister(CPU cpu, uint16_t value);

#endif