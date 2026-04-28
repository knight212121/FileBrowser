#ifndef MODEL_H_
#define MODEL_H_

typedef struct {
    char name[256];
    int is_dir;
} FileEntry;

typedef struct {
    FileEntry *entries;
    int count;
    int selected;
    int capacity;
} DirectoryView;

#endif
