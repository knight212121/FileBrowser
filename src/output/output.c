#include "output.h"
#include "../terminal/terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct abuf {
    char *b;
    int len;
};

struct abuf ab = {NULL, 0};

void append_buffer(const char *s, int len) {
    char *new = realloc(ab.b, ab.len + len);

    if (new == NULL)
        return;
    memcpy(&new[ab.len], s, len);
    ab.b = new;
    ab.len += len;
}

void free_buffer() { free(ab.b); }

void refresh_screen() {
    write(STDOUT_FILENO, "\x1b[2J", 4); // Remove all text from the screen
    write(STDOUT_FILENO, "\x1b[H", 3);  // Move cursor to the top
}

void draw_title(const char *s) {
    append_buffer("\x1b[0;30;47m", 10);
    char welcome[80];
    int welcomelen = snprintf(welcome, sizeof(welcome), "%s", s);
    int padding = (Term.screencols - welcomelen) / 2, i = 0;

    while (padding) {
        append_buffer(" ", 1); // Draw spaces before the name
        padding--;
        i++;
    }
    append_buffer(s, strlen(s)); // Draw the name itself
    i += strlen(s);              // i is to draw spaces after the name
    while (i < Term.screencols) {
        append_buffer(" ", 1); // Draw the spaces
        i++;
    }
    append_buffer("\x1b[0m", 4); // Return back to normal coloring

    append_buffer("\x1b[2E",
                  4); // Move the cursor two lines below at the beginning

    write(STDOUT_FILENO, ab.b, ab.len);
}

void draw_text_at_position(int rows, int cols) {}
