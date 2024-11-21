#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef HAVE_READLINE
    #include <readline/readline.h>
#endif

#include <rhash.h>

#define BUFFER_SIZE 1024

int main() {
    char *line = NULL;
    size_t len = 0;
    size_t read;

    rhash_library_init();

    while (1) {
        #ifdef HAVE_READLINE
            line = readline("> ");
            if (line == NULL) {
                break;
            }
        #else
            // Используем getline
            printf("> ");
            fflush(stdout);
            read = getline(&line, &len, stdin);
            if (read == -1) {
                break;
            }

            if (line[read - 1] == '\n') {
                line[read - 1] = '\0';
            }
        #endif

        char *command = strtok(line, " \t");
        char *argument = strtok(NULL, " \t");

        if (command == NULL || argument == NULL) {
            fprintf(stderr, "Ошибка: некорректная команда\n");
            continue;
        }

        unsigned algorithm;
        if (strcasecmp(command, "MD5") == 0 || strcasecmp(command, "md5") == 0) {
            algorithm = RHASH_MD5;
        } else if (strcasecmp(command, "SHA1") == 0 || strcasecmp(command, "sha1") == 0) {
            algorithm = RHASH_SHA1;
        } else if (strcasecmp(command, "TTH") == 0 || strcasecmp(command, "tth") == 0) {
            algorithm = RHASH_TTH;
        } else {
            fprintf(stderr, "Ошибка: неподдерживаемый алгоритм '%s'\n", command);
            continue;
        }

        int uppercase = (command[0] >= 'A' && command[0] <= 'Z');
        unsigned char hash[64];
        char output[130];
        int res;

        if (argument[0] == '"') {
            char *string = argument + 1; 
            res = rhash_msg(algorithm, string, strlen(string), hash);
        } else {
            char *filepath = argument;
            res = rhash_file(algorithm, filepath, hash);
        }

        if (res < 0) {
            fprintf(stderr, "Ошибка: не удалось вычислить хеш\n");
            continue;
        }

        rhash_print_bytes(output, hash, rhash_get_digest_size(algorithm), uppercase ? RHPR_HEX : RHPR_BASE64);
        printf("%s\n", output);

        #ifdef HAVE_READLINE
            free(line);
        #endif
    }

    return 0;
}