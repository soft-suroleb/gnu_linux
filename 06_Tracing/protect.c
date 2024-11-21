#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>

typedef int (*unlink_type)(const char *path);

int unlink(const char *path) {
    if (strstr(path, "PROTECT") != NULL) {
        printf("Cannot delete protected file: %s\n", path);
        return 0;
    } else {
        return ((unlink_type)(dlsym(RTLD_NEXT, "unlink")))(path);
    }
}
