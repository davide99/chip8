#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

#include <stdint.h>
#define V_REGISTERS 16

enum Register {
    V0 = 0, V1, V2, V3, V4, V5, V6, V7, V8, V9, VA, VB, VC, VD, VE, VF, DT, ST
};

typedef struct CPU_s {
    struct {
        uint8_t VX[V_REGISTERS]; //V0~VF registers
        uint16_t I;
        uint8_t DT, ST; //delay timer register, sound timer register

        uint16_t PC; //Program Counter
        uint8_t SP; //Stack Pointer
    } regs;

    uint16_t stack[16]; //Chip8 define a stack of exactly 16
} CPU;

CPU cpuInit();

int DTthread(void *ptr);

int STthread(void *ptr);

#endif