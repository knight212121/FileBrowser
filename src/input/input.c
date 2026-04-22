#include "input.h"
#include "../error/error.h"
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define CTRL_KEY(k) ((k) & 0x1f)

char read_key() {
    int nread;
    char c;

    while((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) die("read");
    }
    return c;
}

void process_keypress() {
    char c = read_key();

    switch(c) {
        case CTRL_KEY('q'):
            exit(0);
            break;
    }
}
