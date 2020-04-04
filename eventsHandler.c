#include <SDL2/SDL_events.h>
#include "eventsHandler.h"

static int kbThreadFn(void *ptr) {
    SDL_Event event;

    while (1) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_0:
                    case SDLK_KP_0:
                        printf("0");
                }
            }
        }
    }

    return 0;
}

EventsHandler EHInit(void (*kbCallback)(enum Key key), void (*windowCallback)(enum WinEvent winEvent)) {
    EventsHandler eh = {
        .kbCallback = kbCallback,
        .windowCallback = windowCallback
    };


    return eh;
}
