/**
 * @mainpage Guess the number game
 * @copydetails usage
 * @copydetails game
*/
/**
 * @page usage
 * Usage: `game` [-r]\n
 * Options:
 * 
 * - *-r*  ---  Enable Roman numerals mode
 * - *--help*  ---  Show this help message
 */
/**
 * @page game
 * Implementation of Guess the Number game
 * @section SYNOPSIS
 * `game` [ -r ]
 * @section DESCRIPTION
 * Program asks whether guessed number more than
 * some number or not and then asks more until it guesses
 * the actual number
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#include <stdlib.h>
#include <libgen.h>
#include "config.h"

#define _(STRING) gettext(STRING) /**< Define _ as translate function */


/**
 * @brief Global array containing Roman numerals from 1 to 100.
 *
 * This global array contains string representations of Roman numerals
 * from I (1) to C (100).
 */
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


/**
 * @brief Displays usage information for the program.
 *
 * This function prints out the usage instructions for the program,
 * including available command-line options.
 *
 * @param progName The name of the program as invoked by the user.
 *
 */
void usage(const char* progName) {
    printf(_("Usage: %s [-r]\n"), progName);
    printf(_("Options:\n"));
    printf(_("  -r       Enable Roman numerals mode\n"));
    printf(_("  --help   Show this help message\n"));
}


/**
 * @brief Asks the user if their number is more than the given number.
 *
 * This function prints a question to the user, querying if their number
 * is greater than the specified number. The number can be displayed
 * as either a regular integer or a Roman numeral, based on the isRoman flag.
 *
 * @param isRoman A flag indicating whether to display the number as a Roman numeral.
 *                If non-zero, the number will be shown as a Roman numeral.
 *                If zero, the number will be shown as a regular integer.
 * @param number The number to be compared against, which can be displayed
 *               either as a regular integer or as a Roman numeral.
 */
void ask(int isRoman, int number) {
    printf(_("Is your number more than "));

    if (isRoman) {
        printf("%s", romanNumerals[number]);
    } else {
        printf("%d", number);
    }

    printf(" (y/n)?\n");
}


/**
 * @brief Announces the user's number.
 *
 * This function prints out the user's number, either as a standard integer 
 * or as a Roman numeral, depending on the provided flag. It's used to 
 * display the final outcome once the guessing process is complete.
 *
 * @param isRoman A flag indicating whether to display the number as a Roman numeral.
 *                If non-zero, the number will be shown as a Roman numeral.
 *                If zero, the number will be shown as a regular integer.
 * @param number The number to be displayed, which can be formatted as a regular 
 *               integer or as a Roman numeral.
 */
void result(int isRoman, int number) {
    printf(_("Your number is "));

    if (isRoman) {
        printf("%s", romanNumerals[number]);
    } else {
        printf("%d", number);
    }

    printf("!\n");
}


/**
 * @brief Main function demonstrating a number guessing game.
 *
 * This program determines a user's number between a specified range
 * using a binary search method. It prompts the user to respond whether
 * their number is more than a given midpoint until the number is found.
 *
 * The program uses internationalization functions to support different
 * languages for the prompts, assuming appropriate translations are available.
 *
 * The user should input 'y' for "yes" and 'n' for "no" to the prompt asking if
 * their number is greater than the given number.
 *
 * @return Returns 0 upon successful completion.
 */
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

    int useRomanNumerals = 0;

    if (argc > 2) {
        usage(argv[0]);
    }

    if (argc > 1) {
        if (strcmp(argv[1], "-r") == 0) {
            useRomanNumerals = 1;
        } else if (strcmp(argv[1], "--help") == 0) {
            usage(argv[0]);
            return 0;
        } else {
            printf("Unknown option: %s\n", argv[1]);
            usage(argv[0]);
            return 1;
        }
    }

    int left = 0, right = 100;
	char input[10];

    while (left < right) {
        int mid = (left + right) / 2;

        ask(useRomanNumerals, mid);
	    gets(input);

        if (input[0] == 'y') {
            left = mid + 1;
        } else if (input[0] == 'n') {
            right = mid;
        } else {
            continue; /**< If response not 'y' or 'n' then program asks again */
        }
    }

    result(useRomanNumerals, left);

    return 0;
}
