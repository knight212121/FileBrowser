#include "app.h"
#include "../output/output.h"
#include "../model/model.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void show_directory_content(const char *s) {
    DIR *dir;
    struct dirent *entry;
    DirectoryView dv;
    dv.capacity = 16;
    dv.count = 0;
    dv.selected = 0;
    dv.entries = malloc(dv.capacity * sizeof(FileEntry));
    int i = 0;

    dir = opendir(s);
    if (dir != NULL) {
        while((entry = readdir(dir)) != NULL) {
            strncpy(dv.entries[i].name, entry->d_name, 256);
            dv.entries[i].is_dir = (entry->d_type == DT_DIR);
            i++;
            dv.count++;
            if (dv.count >= dv.capacity) {
                dv.capacity *= 2;
                dv.entries = realloc(dv.entries, dv.capacity * sizeof(FileEntry));
            }
        }
    }
    closedir(dir);

    write_directory_to_screen(dv);
}
