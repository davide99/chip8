#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H

typedef struct CHIP8_s *CHIP8;

CHIP8 chip8Init();

void chip8Free(CHIP8 chip8);

#endif
