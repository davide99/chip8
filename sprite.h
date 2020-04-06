#ifndef CHIP8_SPRITE_H
#define CHIP8_SPRITE_H

#include <stdint.h>

#define CHAR_SPRITES 16
#define SPRITE_CHAR_HEIGHT 5
#define FIRST_CHAR_SPRITE_OFFSET 0x050

typedef struct {
    uint8_t *data;
    uint8_t width, height;
} Sprite;

Sprite spriteInit(uint8_t height);

void spriteGenCharInMemory(uint8_t *mem);

Sprite spriteReadFromMemory(uint8_t *data, uint8_t height);

#endif
