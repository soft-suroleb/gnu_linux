#include <stdio.h>
#include <libintl.h>
#include <locale.h>
#include <stdlib.h>
#include <libgen.h>
#include "config.h"

#define _(STRING) gettext(STRING)

int main() {
    setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

    int left = 0, right = 100;
	char input[10];

    while (left < right) {
        int mid = (left + right) / 2;

        printf(_("Is your number more than %d (y/n)?\n"), mid);
	gets(input);

        if (input[0] == 'y') {
            left = mid + 1;
        } else if (input[0] == 'n') {
            right = mid;
        } else {
            continue;
        }
    }

    printf(_("Your number is %d!\n"), left);

    return 0;
}
