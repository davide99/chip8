#include "display.h"
#include "utils.h"
#include <stdlib.h>

#define DISP_WIDTH 64
#define DISP_HEIGHT 32
#define SCALING_FACTOR 10
#define BG_COLOR 0x0080FFFFu
#define FG_COLOR 0xCCE0FFFFu

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

    display.window = SDL_CreateWindow("", 50, 50, display.winWidth, display.winHeight, 0);
    //SDL_CreateWindowAndRenderer(display.winWidth, display.winHeight, 0, &display.window, &display.renderer);

    //SDL_SetWindowPosition(display.window, 50, 50);
    display.renderer = SDL_CreateRenderer(display.window, -1, SDL_RENDERER_SOFTWARE);
    SDL_RenderSetScale(display.renderer, SCALING_FACTOR, SCALING_FACTOR);
    dispClear(display);

    return display;
}

uint8_t dispDispSprite(Display display, Sprite sprite, uint8_t x, uint8_t y) {
    //TODO: Dxyn
    unsigned int old;
    uint8_t i, j, ret = 0;

    SDL_SetRenderDrawColor(display.renderer, DWORD2RGBA(FG_COLOR));

    for (i = 0; i < sprite.height; i++)
        for (j = 0; j < sprite.width; j++)
            if (GETNBIT(sprite.data[i], j)) {
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
    SDL_SetRenderDrawColor(display.renderer, DWORD2RGBA(BG_COLOR));
    SDL_RenderClear(display.renderer);
}

void dispFree(Display display) {
    SDL_DestroyRenderer(display.renderer);
    SDL_DestroyWindow(display.window);
}
