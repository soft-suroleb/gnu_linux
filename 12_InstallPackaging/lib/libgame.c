#include "libgame.h"

const char* romanNumerals[100] = {
    "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X",
    "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX",
    "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX",
    "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL",
    "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L",
    "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX",
    "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX",
    "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX",
    "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC",
    "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"
};


void usage(const char* progName) {
    printf(_("Usage: %s [-r]\n"), progName);
    printf(_("Options:\n"));
    printf(_("  -r       Enable Roman numerals mode\n"));
    printf(_("  --help   Show this help message\n"));
}


void ask(int isRoman, int number) {
    printf(_("Is your number more than "));

    if (isRoman) {
        printf("%s", romanNumerals[number]);
    } else {
        printf("%d", number);
    }

    printf(" (y/n)?\n");
}


void result(int isRoman, int number) {
    printf(_("Your number is "));

    if (isRoman) {
        printf("%s", romanNumerals[number]);
    } else {
        printf("%d", number);
    }

    printf("!\n");
}
