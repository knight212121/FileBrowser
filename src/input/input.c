#include "input.h"
#include "../terminal/terminal.h"
#include <asm-generic/errno-base.h>
#include <stdlib.h>
#include <unistd.h>

#define CTRL_KEY(k) ((k) & 0x1f)

void process_keypress() {
    char c = read_key();

    switch(c) {
        case CTRL_KEY('q'):
            exit(0);
            break;
    }
}
