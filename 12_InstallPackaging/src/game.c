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
#include "../lib/libgame.h"

#define _(STRING) gettext(STRING) /**< Define _ as translate function */


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
