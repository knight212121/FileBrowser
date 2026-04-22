#include "terminal.h"
#include "../error/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

terminal_config Term;

void exit_raw_mode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &Term.orig_termios) == -1)
        die("tcsetattr");
}

void enter_raw_mode() {
    if (tcgetattr(STDIN_FILENO, &Term.orig_termios) == -1)
        die("tcgetattr");
    atexit(exit_raw_mode);

    struct termios raw = Term.orig_termios;
    raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag &= ~(CS8);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

int get_window_size_fallback() { // The logic is if ioctl fails, we put the
                                 // cursor at the bottom right end of
    char buf[32]; // the screen and use 6n command that gives us the position of
                  // cursor and thus get the rows and cols
    unsigned int i = 0;
    if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
        return -1;
    while (i < sizeof(buf) - 1) {
        if (read(STDIN_FILENO, &buf[i], 1) != 1)
            break;
        if (buf[i] == 'R')
            break;
        i++;
    }
    buf[i] = '\0';
    if (buf[0] != '\x1b' || buf[1] != '[')
        return -1;
    if (sscanf(&buf[2], "%d;%d", &Term.screenrows, &Term.screencols) != 2)
        return -1;
    return 0;
}

void get_window_size() {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)
            die("get_window_size_fallback - setting cursor to the end");
        if (get_window_size_fallback() == -1)
            die("get_window_size_fallback");
    } else {
        Term.screencols = ws.ws_col;
        Term.screenrows = ws.ws_row;
    }
}
