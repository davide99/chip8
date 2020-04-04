#include <SDL2/SDL.h>
#include "eventsHandler.h"

static int eventsThreadFn(void *ptr) {
    SDL_Event event;
    EventsHandler *eh = ptr;

    while (1) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                eh->windowCallback(WIN_QUIT);
                break;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_0:
                    case SDLK_KP_0:
                        eh->kbCallback(K0);
                        break;
                }
            }
        }
    }

    return 0;
}

EventsHandler EHInit(void (*kbCallback)(enum Key), void (*windowCallback)(enum WinEvent)) {
    EventsHandler eh = {
            .kbCallback = kbCallback,
            .windowCallback = windowCallback
    };

    SDL_DetachThread(SDL_CreateThread(eventsThreadFn, "eventsThread", &eh));

    return eh;
}
