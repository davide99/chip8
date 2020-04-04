#include "chip8.h"

int main(int argc, char **argv) {
    /*SDL_Event event;
    -SDL_Renderer *renderer;
    -SDL_Window *window;

    -SDL_Init(SDL_INIT_VIDEO);
    -SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    -SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    -SDL_RenderClear(renderer);

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

    CHIP8 chip8 = chip8Init("rom.ch8");


    return 0;
}