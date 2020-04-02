#ifndef CHIP8_SPRITE_H
#define CHIP8_SPRITE_H

#include <stdint.h>
#include <stdbool.h>

#define CHAR_SPRITES 16

typedef struct {
    uint8_t *data;
    uint8_t width, height;
} Sprite;

Sprite spriteInit(uint8_t height, bool zeroFill);

Sprite *spriteGenChar();

#endif
