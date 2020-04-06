#include "chip8.h"

int main(int argc, char **argv) {
    CHIP8 chip8 = chip8Init("kb_test.ch8");
    chip8Free(chip8);

    return 0;
}