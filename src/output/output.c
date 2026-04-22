#include "output.h"
#include <unistd.h>

void refresh_screen() {
    write(STDOUT_FILENO, "\x1b[2J", 4); // Remove all text from the screen
    write(STDOUT_FILENO, "\x1b[H", 3); // Move cursor to the top
}
