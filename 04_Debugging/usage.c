#include <stdio.h>
#include "usage.h"

void usage(char *prog) {
    fprintf(
        stderr, "%s: Print arithmetic progression\n"\
        "Usage: \t%s stop : ([0, 1, ..., stop - 1])\n"\
        "\t%s start stop : ([start, start + 1, ..., stop - 1])\n"
        "\t%s start stop step : ([start, start + step, ..., stop - 1])\n",
        prog, prog, prog, prog
    );
}
