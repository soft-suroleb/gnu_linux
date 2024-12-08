
/**
 * @brief Global array containing Roman numerals from 1 to 100.
 *
 * This global array contains string representations of Roman numerals
 * from I (1) to C (100).
 */
extern const char* romanNumerals[100];


/**
 * @brief Displays usage information for the program.
 *
 * This function prints out the usage instructions for the program,
 * including available command-line options.
 *
 * @param progName The name of the program as invoked by the user.
 *
 */
void usage(const char* progName);


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
void ask(int isRoman, int number);

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
void result(int isRoman, int number);
