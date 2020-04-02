#ifndef CHIP8_DISPLAY_H
#define CHIP8_DISPLAY_H

/*
 * +------------------+
 * |(0,0)       (63,0)|
 * |                  |
 * |(0,31)     (63,31)|
 * +------------------+
 */


#define DISP_WIDTH 64
#define DISP_HEIGHT 32

typedef struct {

} Display;

Display dispInit();

void dispClear(Display display);

#endif
