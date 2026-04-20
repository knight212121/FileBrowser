#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct Config {
    struct termios orig_termios;
};
struct Config C;

void die(const char *s) {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
    perror(s);
    exit(1);
}

void exit_raw_mode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &C.orig_termios) == -1)
        die("tcsetattr");
}

void enter_raw_mode() {
    if (tcgetattr(STDIN_FILENO, &C.orig_termios) == -1) 
        die("tcgetattr");
    atexit(exit_raw_mode);

    struct termios raw = C.orig_termios;
    raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag &= ~(CS8);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}
