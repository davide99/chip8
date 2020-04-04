#include "utils.h"

#include <openssl/rand.h>

uint8_t randomUInt8() {
    uint8_t v;

    if (!RAND_bytes(&v, sizeof(v)))
        return 1;

    return v;
}

void showMessageBox(const char *title, const char *text, enum MbType type) {
    SDL_ShowSimpleMessageBox(type, title, text, NULL);
}
