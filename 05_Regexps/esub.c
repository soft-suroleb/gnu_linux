#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

#define MAX_SUBSTITUTION_LENGTH 1024
#define MAX_BACKREF_COUNT 100
#define MAX_BAGS 10

#define bool int
#define true 1
#define false 0

int insert_backref(
    char* result,
    int *idx,
    const char *input_str,
    const int group_num,
    const int num_groups,
    const regmatch_t *pmatch
) {
    if (group_num > num_groups) {
        fprintf(stderr, "No such group: %d\n", group_num);
        return 1;
    }

    int group_s = pmatch[group_num].rm_so;
    int group_e = pmatch[group_num].rm_eo;
    int group_len = group_e - group_s;
    strncpy(result + *idx, input_str + group_s, group_len);
    (*idx) += group_len;

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s regexp substitution string\n", argv[0]);
        return 1;
    }

    const char *pattern = argv[1];
    const char *sub = argv[2];
    const char *input_str = argv[3];

    regex_t regex;
    regmatch_t pmatch[MAX_BAGS];
    int ret_code;
    char err_buffer[256];

    ret_code = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret_code != 0) {
        regerror(ret_code, &regex, err_buffer, sizeof(err_buffer));
        fprintf(stderr, "Regex compilation error: %s\n", err_buffer);
        regfree(&regex);
        return 1;
    }

    ret_code = regexec(&regex, input_str, MAX_BAGS, pmatch, 0);

    if (ret_code == REG_NOMATCH) {
        printf("%s\n", input_str);
        regfree(&regex);
        return 0;
    }

    if (ret_code != 0) {
        regerror(ret_code, &regex, err_buffer, sizeof(err_buffer));
        fprintf(stderr, "Regex execution error: %s\n", err_buffer);
        regfree(&regex);
        return 1;
    }

    int num_groups = regex.re_nsub > MAX_BAGS ? MAX_BAGS : regex.re_nsub; 

    char sub_result[MAX_SUBSTITUTION_LENGTH];
    int res_index = 0;
    int sub_len = strlen(sub);
    int backref_count = 0;
    char last_char = 0;
    bool is_ref = false;

    for (int i = 0; i < sub_len; i++) {
        char c = sub[i];

        if (isdigit(c) && last_char == '\\') {
            is_ref = true;
            last_char = c;
            backref_count++;

            if (backref_count > MAX_BACKREF_COUNT) {
                fprintf(stderr, "Too much backrefs: >%d\n", MAX_BACKREF_COUNT);
                return 1;
            }

            continue;
        }

        if (isdigit(c) && is_ref) {
            fprintf(stderr, "Big backref: >%d\n", MAX_BAGS - 1);
            regfree(&regex);
            return 1;
        }

        if (is_ref && isdigit(last_char)) {
            is_ref = false;
            ret_code = insert_backref(sub_result, &res_index, input_str, last_char - '0', num_groups, pmatch);
            if (ret_code != 0) {
                return 1;
            }
        }

        if (c == '\\') {
            if (last_char == '\\') {
                sub_result[res_index++] = c;
            }

            last_char = last_char == '\\' ? 0 : c;
            continue;
        }

        sub_result[res_index++] = c;
        last_char = c;
    }

    if (is_ref && isdigit(last_char)) {
        ret_code = insert_backref(sub_result, &res_index, input_str, last_char - '0', num_groups, pmatch);
        if (ret_code != 0) {
            return 1;
        }
    }
    sub_result[res_index] = '\0';

    int match_s = pmatch[0].rm_so;
    int match_e = pmatch[0].rm_eo;

    printf("%.*s%s%s\n", match_s, input_str, sub_result, input_str + match_e);
    regfree(&regex);
    return EXIT_SUCCESS;
}