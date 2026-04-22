#include "terminal/terminal.h"
#include "input/input.h"
#include "output/output.h"
#include <stdio.h>
#include <unistd.h>

int main() {
    enter_raw_mode();
    get_window_size();

    printf("%dx%d", Term.screenrows, Term.screencols);

    while(1) {
        refresh_screen();
        process_keypress();
    }
    return 0;
}
