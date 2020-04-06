#ifndef CHIP8_KBQUEUE_H
#define CHIP8_KBQUEUE_H

#include <SDL2/SDL_keycode.h>
#include <stdint.h>

#define KCODE2INT(X) ((uint8_t)((X>=SDLK_0 && X<=SDLK_9)?((uint8_t)(X-SDLK_0)):((X>=SDLK_a && X<=SDLK_f)?((uint8_t)(X-SDLK_a+10u)):(255u))))

typedef struct KBQueue_s *KBQueue;

KBQueue kbQueueInit();

int kbQueueIsEmpty(KBQueue queue);

void kbQueueEnqueue(KBQueue kbQueue, uint8_t c);

uint8_t kbQueueDequeue(KBQueue kbQueue);

void kbQueueFree(KBQueue kbQueue);

#endif
