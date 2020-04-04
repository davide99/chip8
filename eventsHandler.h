#ifndef CHIP8_EVENTSHANDLER_H
#define CHIP8_EVENTSHANDLER_H

enum Key {
    K0 = '0', K1 = '1', K2 = '2', K3 = '3', K4 = '4', K5 = '5', K6 = '6', K7 = '7', K8 = '8', K9 = '9',
    KA = 'A', KB = 'B', KC = 'C', KD = 'D', KE = 'E', KF = 'F'
};

enum WinEvent{
    WIN_QUIT
};

typedef struct {
    void (*kbCallback)(enum Key key);

    void (*windowCallback)(enum WinEvent winEvent);
} EventsHandler;

EventsHandler EHInit(void (*kbCallback)(enum Key key), void (*windowCallback)(enum WinEvent winEvent));

#endif
