#ifndef CHIP8_UTILS_H
#define CHIP8_UTILS_H

#include <stdint.h>
#include <SDL2/SDL.h>

/*
 * Nibble extraction macros
 *
 *      Word = N1|N2|N3|N4 = 16 bit
 *                    ^  ^--Nibble 4 = 4 bit
 *                    +-----Nibble 3...
 *
 * The nibble is returned as a uint8_t
 */

#define NIBBLE1(X) ((uint8_t) ((uint8_t)(X >> 12u)))
#define NIBBLE2(X) ((uint8_t) ((uint8_t)(X >> 8u) & 0xFu))
#define NIBBLE3(X) ((uint8_t) ((uint8_t)(X >> 4u) & 0xFu))
#define NIBBLE4(X) ((uint8_t) ((uint8_t)(X & 0xFu)))

#define LOWBYTE(X) ((uint8_t)(X & 0xFFu))
#define LOWEST12BIT(X) (X & 0xFFFu)

#define GETNBIT(X, N) ((uint8_t)(X >> N) & 1u)

#define DWORD2RGBA(X) X>>24u, X >> 16u & 0xFFu, X >> 8u & 0xFFu, X & 0xFFu

enum MbType {
    MB_ERROR = SDL_MESSAGEBOX_ERROR,
    MB_WARN = SDL_MESSAGEBOX_WARNING,
    MB_INFO = SDL_MESSAGEBOX_INFORMATION
};

uint8_t randomUInt8();

void showMessageBox(const char *title, const char *text, enum MbType type);

#endif
