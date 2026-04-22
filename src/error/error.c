#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void die(const char *s) {
    write(STDOUT_FILENO, "\x1b[2J", 4); // Clear the screen
    write(STDOUT_FILENO, "\x1b[H", 3); // Move the cursor to the top
    perror(s);
    exit(1);
}
