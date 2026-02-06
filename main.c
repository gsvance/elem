/*
This file contains the main function and a few supporting functions for elem
It takes a list of command line arguments and finds them in the periodic table
An element may be looked up by its proton number, its symbol, or its full name
The output is an entry from the periodic table containing all that information
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbols.c"
#include "names.c"

// Define a boolean type for convenience
typedef enum {false, true} bool;

bool is_number(char * string);
void title_case(char * string);

int main(int argc, char * argv[])
{
    int i;
    char * arg;
    int code = 0;
    int nz;
    char * symbol;
    char * name;

    // Print error message and exit if no args
    if (argc < 2)
    {
        fprintf(stderr, "usage: %s lookup [lookup ...]\n", argv[0]);
        return 1;
    }

    // Loop through the arguments and look up each one in turn
    for (i = 1; i < argc; i++)
    {
        arg = argv[i];

        // If the argument is a number, try to make nz out of it
        if (is_number(arg))
        {
            // Convert the string to an integer
            nz = atoi(arg);

            // Check that nz is actually on the periodic table
            if ((nz < 0) || (nz > 118))
            {
                // Print an error, set the return code, and go to next arg
                fprintf(stderr, "invalid nz value %d\n", nz);
                code = 2;
                continue;
            }

            // For valid nz, look up the associated symbol and name
            symbol = symbols[nz];
            name = names[nz];
        }
        // If the argument isn't a number, it must be a symbol or a name
        else
        {
            // Convert argument to title case for comparison with arrays
            title_case(arg);

            // Try every proton number and see if any of them match
            for (nz = 0; nz <= 118; nz++)
            {
                // Get the symbol and name for the element with this nz
                symbol = symbols[nz];
                name = names[nz];

                // Break out of the search if either one matches the argument
                if ((strcmp(arg, symbol) == 0) || (strcmp(arg, name) == 0))
                    break;
            }

            // If nz reaches 119, then the loop terminated without breaking
            if (nz == 119)
            {
                // Not found, so error and change exit code, go to next arg
                fprintf(stderr, "no result for '%s'\n", arg);
                code = 2;
                continue;
            }
        }

        // If this line reached, print the periodic table entry we found
        printf("%d\t%s\t%s\n", nz, symbol, name);
    }

    // Exit with the return code
    return code;
}

// Return whether the string is numeric (with possible leading '-')
bool is_number(char * string)
{
    int i = 0;
    char c;

    // Negative numbers can start with a '-', skip it
    if (string[0] == '-')
        i++;

    // Empty strings and lone hypens are not numbers
    if (string[i] == '\0')
        return false;

    do
    {
        c = string[i++];

        // If anything isn't a digit or '\0', then it's not a number
        if (((c < '0') || (c > '9')) && (c != '\0'))
            return false;
    }
    while (c != '\0');

    // If this point is reached, the string really is a number
    return true;
}

// Change string capitalization to title case so it matches the lookup arrays
void title_case(char * string)
{
    int diff;
    bool start = true;
    int i = 0;
    char c;

    diff = 'A' - 'a';

    do
    {
        c = string[i];

        // If a lowercase letter is found
        if ((c >= 'a') && (c <= 'z'))
        {
            // Capitalize if it begins a word, mark next as not a word start
            if (start)
            {
                string[i] += diff;
                start = false;
            }
        }
        // If an uppercase letter is found
        else if ((c >= 'A') && (c <= 'Z'))
        {
            // If a word has started, mark next as not a word start
            if (start)
                start = false;

            // If not at the start of a word, make it lowercase instead
            else
                string[i] -= diff;
        }
        // Non-alphabetic characters mark the end of a word
        else
            start = true;

        i++;
    }
    while (c != '\0');
}
