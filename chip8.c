#include "chip8.h"
#include "cpu.h"
#include "memory.h"
#include "display.h"
#include "sprite.h"
#include "keyboard.h"
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <SDL2/SDL.h>

struct CHIP8_s {
    CPU cpu;
    Memory memory;
    Display display;
};

static void _execute(CHIP8 chip8) {
    uint16_t opcode, tmp;
    Sprite sprite;
    uint8_t i;

    while (1) {
        opcode = memReadWord(chip8->memory, chip8->cpu.regs.PC);

        switch (opcode >> 12u) { //MSB
            case 0x0:
                switch (opcode & 0xFFFu) {
                    case 0x0E0: //CLS: display clear
                        dispClear(chip8->display);
                        break;

                    case 0x0EE: //RET: return from a subroutine
                        chip8->cpu.regs.PC = chip8->cpu.stack[chip8->cpu.regs.SP];
                        chip8->cpu.regs.SP--;
                        break;
                }
                break;

            case 0x1: //JP: jump @ address
                chip8->cpu.regs.PC = (opcode & 0xFFFu) - 2;
                break;

            case 0x2: //CALL: call subroutine @ address
                chip8->cpu.regs.SP++;
                chip8->cpu.stack[chip8->cpu.regs.SP] = chip8->cpu.regs.PC;
                chip8->cpu.regs.PC = (opcode & 0xFFFu) - 2;
                break;

            case 0x3: //3xkk - SE Vx, byte: skip next instruction if Vx==kk
                if (chip8->cpu.regs.VX[opcode >> 8u & 0xFu] == (opcode & 0xFFu))
                    chip8->cpu.regs.PC += 2;
                break;

            case 0x4: //4xkk - SNE Vx, byte: skip next instruction if Vx!=kk
                if (chip8->cpu.regs.VX[opcode >> 8u & 0xFu] != (opcode & 0xFFu))
                    chip8->cpu.regs.PC += 2;
                break;

            case 0x5: //5xy0 - SE Vx, Vy: skip next instruction if Vx==Vy
                if (chip8->cpu.regs.VX[opcode >> 8u & 0xFu] == chip8->cpu.regs.VX[opcode >> 4u & 0xFu])
                    chip8->cpu.regs.PC += 2;
                break;

            case 0x6: //6xkk - LD Vx, byte: set Vx = kk
                chip8->cpu.regs.VX[opcode >> 8u & 0xFu] = opcode & 0xFFu;
                break;

            case 0x7: //7xkk - ADD Vx, byte: set Vx=Vx+kk
                chip8->cpu.regs.VX[opcode >> 8u & 0xFu] += opcode & 0xFF;
                break;

            case 0x8:
                switch (opcode & 0xFu) {
                    case 0: //8xy0 - LD Vx, Vy: set Vx=Vy
                        chip8->cpu.regs.VX[opcode >> 8u & 0xFu] = chip8->cpu.regs.VX[opcode >> 4u & 0xFu];
                        break;

                    case 1: //8xy1 - OR Vx, Vy: set Vx = Vx | Vy
                        chip8->cpu.regs.VX[opcode >> 8u & 0xFu] |= chip8->cpu.regs.VX[opcode >> 4u & 0xFu];
                        break;

                    case 2: //8xy2 - AND Vx, Vy: set Vx = Vx & Vy
                        chip8->cpu.regs.VX[opcode >> 8u & 0xFu] &= chip8->cpu.regs.VX[opcode >> 4u & 0xFu];
                        break;

                    case 3: //8xy3 - XOR Vx, Vy: set Vx = Vx ^ Vy
                        chip8->cpu.regs.VX[opcode >> 8u & 0xFu] ^= chip8->cpu.regs.VX[opcode >> 4u & 0xFu];
                        break;

                    case 4: //8xy4 - ADD Vx, Vy: set Vx = Vx + Vy, set VF = carry
                        tmp = chip8->cpu.regs.VX[opcode >> 8u & 0xFu] + chip8->cpu.regs.VX[opcode >> 4u & 0xFu];
                        chip8->cpu.regs.VX[opcode >> 8u & 0xFu] += chip8->cpu.regs.VX[opcode >> 4u & 0xFu];

                        chip8->cpu.regs.VX[0xF] = tmp > 255;
                        break;

                    case 5: //8xy5 - SUB Vx, Vy: set Vx = Vx-Vy, set VF = NOT borrow
                        chip8->cpu.regs.VX[0xF] =
                                chip8->cpu.regs.VX[opcode >> 8u & 0xFu] > chip8->cpu.regs.VX[opcode >> 4u & 0xFu];
                        chip8->cpu.regs.VX[opcode >> 8u & 0xFu] -= chip8->cpu.regs.VX[opcode >> 4u & 0xFu];
                        break;

                    case 6: //8xy6 - SHR Vx {, Vy}: Set Vx = Vx SHR 1
                        chip8->cpu.regs.VX[0xF] = chip8->cpu.regs.VX[opcode >> 8u & 0xFu] & 0x1;
                        chip8->cpu.regs.VX[opcode >> 8u & 0xFu] /= 2;
                        break;

                    case 7: //8xy7 - SUBN Vx, Vy: Set Vx = Vy - Vx, set VF = NOT borrow.
                        chip8->cpu.regs.VX[0xF] =
                                chip8->cpu.regs.VX[opcode >> 4u & 0xFu] > chip8->cpu.regs.VX[opcode >> 8u & 0xFu];
                        chip8->cpu.regs.VX[opcode >> 8u & 0xFu] -= chip8->cpu.regs.VX[opcode >> 4u & 0xFu];
                        break;

                    case 8: //8xyE - SHL Vx {, Vy}: Set Vx = Vx SHL 1.
                        chip8->cpu.regs.VX[0xF] = chip8->cpu.regs.VX[opcode >> 8u & 0xFu] & 0x1;
                        chip8->cpu.regs.VX[opcode >> 8u & 0xFu] *= 2;
                        break;
                }
                break;

            case 0x9: //9xy0 - SNE Vx, Vy: Skip next instruction if Vx != Vy
                if (chip8->cpu.regs.VX[opcode >> 8u & 0xFu] != chip8->cpu.regs.VX[opcode >> 4u & 0xFu])
                    chip8->cpu.regs.PC += 2;
                break;

            case 0xA: //Annn - LD I, addr: Set I = nnn
                chip8->cpu.regs.I = opcode & 0xFFFu;
                break;

            case 0xB: //Bnnn - JP V0, addr: Jump to location nnn + V0
                chip8->cpu.regs.PC = opcode & 0xFFFu + chip8->cpu.regs.VX[0] - 2;
                break;

            case 0xC: //Cxkk - RND Vx, byte: Set Vx = random byte AND kk
                //TODO: better rand
                chip8->cpu.regs.VX[opcode >> 8u & 0xF] = ((uint8_t) rand() % 255) & (opcode & 0xFF);
                break;

            case 0xD:
                //Dxyn - DRW Vx, Vy, nibble
                //Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
                sprite = spriteReadFromMemory(chip8->memory.data + chip8->cpu.regs.I, opcode & 0xFu);
                chip8->cpu.regs.VX[0xF] =
                        dispDispSprite(chip8->display, sprite, opcode >> 8u & 0xFu, opcode >> 4u & 0xFu);
                break;

            case 0xE:
                switch (opcode & 0xFFu) {
                    case 0x9E:
                        //Ex9E - SKP Vx
                        //Skip next instruction if key with the value of Vx is pressed.
                        if (chip8->cpu.regs.VX[opcode >> 8u & 0xFu] == K0)
                            chip8->cpu.regs.PC += 2; //TODO: sistemare, sul down
                        break;

                    case 0xA1:
                        //ExA1 - SKNP Vx
                        //Skip next instruction if key with the value of Vx is not pressed.
                        if (chip8->cpu.regs.VX[opcode >> 8u & 0xFu] != K0)
                            chip8->cpu.regs.PC += 2; //TODO: sistemare, sul down
                        break;
                }
                break;

            case 0xF:
                switch (opcode & 0xFFu) {
                    case 0x07: //Fx07 - LD Vx, DT: Set Vx = delay timer value.
                        chip8->cpu.regs.VX[opcode >> 8u & 0xFu] = chip8->cpu.regs.DT;
                        break;

                    case 0x0A:
                        //Fx0A - LD Vx, K
                        //Wait for a key press, store the value of the key in Vx.
                        //TODO: wait 'til any key is pressed  v--Key
                        chip8->cpu.regs.VX[opcode >> 8u & 0xFu] = 0;
                        break;

                    case 0x15: //Fx15 - LD DT, Vx: Set delay timer = Vx.
                        chip8->cpu.regs.DT = chip8->cpu.regs.VX[opcode >> 8u & 0xFu];
                        SDL_DetachThread(SDL_CreateThread(DTthread, "DTthread", &chip8->cpu));
                        break;

                    case 0x18: //Fx18 - LD ST, Vx: Set sound timer = Vx.
                        chip8->cpu.regs.ST = chip8->cpu.regs.VX[opcode >> 8u & 0xFu];
                        SDL_DetachThread(SDL_CreateThread(STthread, "STthread", &chip8->cpu));
                        break;

                    case 0x1E: //Fx1E - ADD I, Vx: Set I = I + Vx.
                        chip8->cpu.regs.I += chip8->cpu.regs.VX[opcode >> 8u & 0xFu];
                        break;

                    case 0x29: //Fx29 - LD F, Vx: Set I = location of sprite for digit Vx.
                        chip8->cpu.regs.I = (opcode >> 8u & 0xFu * SPRITE_CHAR_HEIGHT) + FIRST_CHAR_SPRITE_OFFSET;
                        break;

                    case 0x33:
                        //Fx33 - LD B, Vx
                        //Store BCD representation of Vx in memory locations I, I+1, and I+2.
                        chip8->memory.data[chip8->cpu.regs.I + 2] = chip8->cpu.regs.VX[opcode >> 8u & 0xF] % 10;
                        chip8->memory.data[chip8->cpu.regs.I + 1] = chip8->cpu.regs.VX[opcode >> 8u & 0xF] / 10 % 10;
                        chip8->memory.data[chip8->cpu.regs.I + 0] = chip8->cpu.regs.VX[opcode >> 8u & 0xF] / 100 % 10;
                        break;

                    case 0x55:
                        //Fx55 - LD [I], Vx
                        //Store registers V0 through Vx in memory starting at location I.
                        for (i = 0; i <= chip8->cpu.regs.VX[opcode >> 8u & 0xF]; i++)
                            chip8->memory.data[chip8->cpu.regs.I + i] = chip8->cpu.regs.VX[i];
                        break;

                    case 0x65:
                        //Fx65 - LD Vx, [I]
                        //Read registers V0 through Vx from memory starting at location I.
                        for (i = 0; i <= chip8->cpu.regs.VX[opcode >> 8u & 0xF]; i++)
                            chip8->cpu.regs.VX[i] = chip8->memory.data[chip8->cpu.regs.I + i];
                        break;
                }
                break;
        }

        chip8->cpu.regs.PC += 2;
    }
}


CHIP8 chip8Init(const char *romFile) {
    CHIP8 chip8 = malloc(sizeof(struct CHIP8_s));

    chip8->cpu = cpuInit();
    chip8->memory = memInit();
    chip8->display = dispInit();
    spriteGenCharInMemory(chip8->memory.data);

    srand(time(NULL));

    memCopyROMFromFile(chip8->memory, romFile);

    SDL_Init(SDL_INIT_EVERYTHING); //TODO: Something better...

    _execute(chip8);

    return chip8;
}

void chip8Free(CHIP8 chip8) {
    free(chip8);
}
