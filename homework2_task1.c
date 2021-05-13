#include <stdio.h>

#define MAX_LINE 100
#define MAX_PATH 1000

struct Station {
    char type[2]={'m','b'};
    unsigned short line_nb[MAX_LINE];
    int id;
}

struct Path{
    const struct Station[MAX_PATH];
    unsigned short path_size;
};
