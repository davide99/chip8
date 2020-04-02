#include "sprite.h"
#include <stdlib.h>

#define SPRITE_WIDTH 8
#define SPRITE_MIN_HEIGHT 1
#define SPRITE_MAX_HEIGHT 15
#define SPRITE_CHAR_HEIGHT 5

Sprite spriteInit(uint8_t height, bool zeroFill) {
    uint8_t i;
    Sprite sprite = {.data = NULL, .height = 0, .width = 0};

    if (height < SPRITE_MIN_HEIGHT || height > SPRITE_MAX_HEIGHT)
        return sprite;

    sprite.width = SPRITE_WIDTH;
    sprite.height = height;
    sprite.data = malloc(sizeof(uint8_t) * height);

    for (i = 0; i < height; i++)
        if (zeroFill)
            sprite.data[i] = 0;

    return sprite;
}

Sprite *spriteGenChar() {
    uint8_t i;
    Sprite *charSprites;

    charSprites = malloc(sizeof(Sprite) * SPRITE_CHAR_HEIGHT);

    for (i = 0; i < CHAR_SPRITES; i++)
        charSprites[i] = spriteInit(SPRITE_CHAR_HEIGHT, false);

    //0
    charSprites[0].data[0] = 0xF0;
    charSprites[0].data[1] = 0x90;
    charSprites[0].data[2] = 0x90;
    charSprites[0].data[3] = 0x90;
    charSprites[0].data[4] = 0xF0;

    //1
    charSprites[1].data[0] = 0x20;
    charSprites[1].data[1] = 0x60;
    charSprites[1].data[2] = 0x20;
    charSprites[1].data[3] = 0x20;
    charSprites[1].data[4] = 0x70;

    //2
    charSprites[2].data[0] = 0xF0;
    charSprites[2].data[1] = 0x10;
    charSprites[2].data[2] = 0xF0;
    charSprites[2].data[3] = 0x80;
    charSprites[2].data[4] = 0xF0;

    //3
    charSprites[3].data[0] = 0xF0;
    charSprites[3].data[1] = 0x10;
    charSprites[3].data[2] = 0xF0;
    charSprites[3].data[3] = 0x10;
    charSprites[3].data[4] = 0xF0;

    //4
    charSprites[4].data[0] = 0x90;
    charSprites[4].data[1] = 0x90;
    charSprites[4].data[2] = 0xF0;
    charSprites[4].data[3] = 0x10;
    charSprites[4].data[4] = 0x10;

    //5
    charSprites[5].data[0] = 0xF0;
    charSprites[5].data[1] = 0x80;
    charSprites[5].data[2] = 0xF0;
    charSprites[5].data[3] = 0x10;
    charSprites[5].data[4] = 0xF0;

    //6
    charSprites[6].data[0] = 0xF0;
    charSprites[6].data[1] = 0x80;
    charSprites[6].data[2] = 0xF0;
    charSprites[6].data[3] = 0x90;
    charSprites[6].data[4] = 0xF0;

    //7
    charSprites[7].data[0] = 0xF0;
    charSprites[7].data[1] = 0x10;
    charSprites[7].data[2] = 0x20;
    charSprites[7].data[3] = 0x40;
    charSprites[7].data[4] = 0x40;

    //8
    charSprites[8].data[0] = 0xF0;
    charSprites[8].data[1] = 0x90;
    charSprites[8].data[2] = 0xF0;
    charSprites[8].data[3] = 0x90;
    charSprites[8].data[4] = 0xF0;

    //9
    charSprites[9].data[0] = 0xF0;
    charSprites[9].data[1] = 0x90;
    charSprites[9].data[2] = 0xF0;
    charSprites[9].data[3] = 0x10;
    charSprites[9].data[4] = 0xF0;

    //A
    charSprites[10].data[0] = 0xF0;
    charSprites[10].data[1] = 0x90;
    charSprites[10].data[2] = 0xF0;
    charSprites[10].data[3] = 0x90;
    charSprites[10].data[4] = 0x90;

    //B
    charSprites[11].data[0] = 0xE0;
    charSprites[11].data[1] = 0x90;
    charSprites[11].data[2] = 0xE0;
    charSprites[11].data[3] = 0x90;
    charSprites[11].data[4] = 0xE0;

    //C
    charSprites[12].data[0] = 0xF0;
    charSprites[12].data[1] = 0x80;
    charSprites[12].data[2] = 0x80;
    charSprites[12].data[3] = 0x80;
    charSprites[12].data[4] = 0xF0;

    //D
    charSprites[13].data[0] = 0xE0;
    charSprites[13].data[1] = 0x90;
    charSprites[13].data[2] = 0x90;
    charSprites[13].data[3] = 0x90;
    charSprites[13].data[4] = 0xE0;

    //E
    charSprites[14].data[0] = 0xF0;
    charSprites[14].data[1] = 0x80;
    charSprites[14].data[2] = 0xF0;
    charSprites[14].data[3] = 0x80;
    charSprites[14].data[4] = 0xF0;

    //F
    charSprites[15].data[0] = 0xF0;
    charSprites[15].data[1] = 0x80;
    charSprites[15].data[2] = 0xF0;
    charSprites[15].data[3] = 0x80;
    charSprites[15].data[4] = 0x80;

    return charSprites;
}