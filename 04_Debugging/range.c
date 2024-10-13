#include <stdio.h>
#include <stdlib.h>
#include "usage.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        usage(argv[0]);
        return 1;
    }

    int start = 0;
    int stop;
    int step = 1;

    if (argc == 2) {
        stop = atoi(argv[1]);
    }

    if (argc > 2) {
        start = atoi(argv[1]);
        stop = atoi(argv[2]);
    }

    if (argc == 4) {
        step = atoi(argv[3]);
    }

    for (int i = start; i < stop; i += step) {
        printf("%d\n", i);
    }

    return 0;
}
