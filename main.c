#include <SDL2/SDL.h>
#include <stdio.h>
#include <fvec.h>
#include "cpu.h"

#define WINDOW_WIDTH 600

int main(int argc, char **argv) {
    /*SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    int i;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (i = 0; i < WINDOW_WIDTH; ++i)
        SDL_RenderDrawPoint(renderer, i, i);
    SDL_RenderPresent(renderer);

    while (1) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            } else if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_0:
                    case SDLK_KP_0:
                        printf("0");
                }
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();*/

    CPU cpu = cpuInit(result);
    SDL_Delay(1000);

    return 0;
}