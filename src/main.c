#include "terminal/terminal.h"
#include "input/input.h"
#include "output/output.h"
#include <unistd.h>

int main() {
    enter_raw_mode();
    get_window_size();
    refresh_screen();
    draw_title("Welcome to Fowser");

    while(1) {
        process_keypress();
    }
    return 0;
}
