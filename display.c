#include "display.h"
#include <stdlib.h>

#define DISP_WIDTH 64
#define DISP_HEIGHT 32
#define SCALING_FACTOR 10
#define BG_COLOR 0x0080FFFFu
#define FG_COLOR 0xCCE0FFFFu

#define GET_BIT(X, N) ( ( (X) >> (N) ) & 1 )

Display dispInit() {
    uint8_t i;

    Display display = {
            .height = DISP_HEIGHT,
            .width = DISP_WIDTH,
            .winHeight = DISP_HEIGHT * SCALING_FACTOR,
            .winWidth = DISP_WIDTH * SCALING_FACTOR,
            .mat = malloc(sizeof(int *) * DISP_HEIGHT),
    };

    for (i = 0; i < DISP_HEIGHT; i++)
        display.mat[i] = calloc(DISP_WIDTH, sizeof(int));

    SDL_CreateWindowAndRenderer(display.winWidth, display.winHeight, 0, &display.window, &display.renderer);
    SDL_RenderSetScale(display.renderer, SCALING_FACTOR, SCALING_FACTOR);
    SDL_SetWindowPosition(display.window, 50, 50);

    dispClear(display);

    return display;
}

uint8_t dispDispSprite(Display display, Sprite sprite, uint8_t x, uint8_t y) {
    //TODO: Dxyn
    unsigned int old;
    uint8_t i, ret = 0;
    int8_t a, b, j;

    SDL_SetRenderDrawColor(display.renderer,
                           FG_COLOR >> 24u, FG_COLOR >> 16u & 0xFFu, FG_COLOR >> 8u & 0xFFu, FG_COLOR & 0xFFu);

    for (i = 0; i < sprite.height; i++)
        for (j = sprite.width - 1; j >= 0; j--)
            if (GET_BIT(sprite.data[i], j)) {
                //if (sprite.data[i] >> j & 1u) {
                old = display.mat[y + i][(x + j)];
                display.mat[y + i][(x + j)] ^= 1u;

                if (old && !display.mat[y + i][(x + j)])
                    ret = 1;

                //if (display.mat[y + i][(x + j)] && 1) {
                SDL_RenderDrawPoint(display.renderer, (x + 7 - j) % DISP_WIDTH, (y + i));
                //SDL_RenderPresent(display.renderer);
                //}
            }

    SDL_RenderPresent(display.renderer);

    return ret;
}

void dispClear(Display display) {
    SDL_SetRenderDrawColor(display.renderer,
                           BG_COLOR >> 24u, BG_COLOR >> 16u & 0xFFu, BG_COLOR >> 8u & 0xFFu, BG_COLOR & 0xFFu);
    SDL_RenderClear(display.renderer);
}

void dispFree(Display display) {
    SDL_DestroyRenderer(display.renderer);
    SDL_DestroyWindow(display.window);
}
