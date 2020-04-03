#ifndef CHIP8_DISPLAY_H
#define CHIP8_DISPLAY_H

#include "sprite.h"
#include <stdint.h>
#include <SDL2/SDL.h>

/*
 * +------------------+
 * |(0,0)       (63,0)|
 * |                  |
 * |(0,31)     (63,31)|
 * +------------------+
 */

typedef struct {
    uint8_t width, height;
    SDL_Renderer *renderer;
    SDL_Window *window;
    unsigned int **mat;
} Display;

Display dispInit();

void dispClear(Display display);

uint8_t dispDispSprite(Display display, Sprite sprite, uint8_t x, uint8_t y);

#endif
