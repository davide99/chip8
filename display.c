#include "display.h"
#include <stdlib.h>

#define DISP_WIDTH 64
#define DISP_HEIGHT 32

Display dispInit() {
    uint8_t i;

    Display display = {
            .height = DISP_HEIGHT,
            .width = DISP_WIDTH,
            .mat = malloc(sizeof(int *) * DISP_WIDTH),
    };

    for (i = 0; i < DISP_HEIGHT; i++)
        display.mat[i] = calloc(DISP_HEIGHT, sizeof(int));

    SDL_CreateWindowAndRenderer(DISP_WIDTH, DISP_HEIGHT, 0, &display.window, &display.renderer);

    return display;
}

uint8_t dispDispSprite(Display display, Sprite sprite, uint8_t x, uint8_t y) {
    //TODO: Dxyn
    unsigned int old;
    uint8_t i, j, ret = 0;

    SDL_SetRenderDrawColor(display.renderer, 255, 255, 255, 255);

    for (i = 0; i < sprite.height; i++)
        for (j = 0; j < sprite.width; j++)
            if (sprite.data[i] >> j & 1u) {
                old = display.mat[x + j][y + i];
                display.mat[x + j][y + i] ^= 1u;

                if (old && !display.mat[x + j][y + i])
                    ret = 1;

                SDL_RenderDrawPoint(display.renderer, x + j, y + i);
            }

    SDL_RenderPresent(display.renderer);

    return ret;
}

void dispClear(Display display) {
    SDL_SetRenderDrawColor(display.renderer, 0, 0, 0, 0);
    SDL_RenderClear(display.renderer);
}
