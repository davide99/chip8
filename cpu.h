#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

#include <stdint.h>
#define V_REGISTERS 16

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

CPU cpuInit(uint16_t startingAddress);

int DTthread(void *ptr);

int STthread(void *ptr);

#endif