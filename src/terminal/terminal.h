#ifndef TERMINAL_H_
#define TERMINAL_H_

#include <termios.h>

typedef struct {
    struct termios orig_termios;
    int screenrows;
    int screencols;
} terminal_config;

extern terminal_config Term;

void enter_raw_mode();

void get_window_size();

#endif
