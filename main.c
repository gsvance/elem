// This file contains the main function and a few other functions for the elem program
// Elem takes a list of command line arguments and finds each of them in the periodic table
// A given element may be looked up by its proton number, its symbol, or its full name
// The output is an entry from the periodic table which contains all of that information

// Last edited 10/20/16 by Greg Vance

// Standard libraries are needed
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Get the lookup tables of elemental symbols and names
#include "symbols.h"
#include "names.h"

// Define a boolean type for convenience
typedef enum {false, true} bool;

// Function declarations, defined later on
bool is_number(char * string);
void title_case(char * string);

// Main program for elem
int main(int argc, char * argv[])
{
	// Declarations
	int i;		// Loop index
	char * arg;	// Argument string
	int code = 0;	// Return code, set to success by default
	int nz;		// Proton number for the element
	char * symbol;	// Symbol for the element
	char * name;	// Name of the element
	
	// Make sure there are arguments
	if (argc < 2) {
		// Print error message and exit if no args
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
			// Convert argument to title case for comparison with lookup tables
			title_case(arg);
			
			// Try every proton number and see if anything matches the argument
			for (nz = 0; nz <= 118; nz++)
			{
				// Get the symbol and name for the element with this nz
				symbol = symbols[nz];
				name = names[nz];
				
				// Break out of the search if either one matches the argument
				if ((strcmp(arg, symbol) == 0) || (strcmp(arg, name) == 0))
					break;
			}
			
			// If nz reaches 119, then the for loop terminated without breaking
			if (nz == 119)
			{
				// Means nothing found, so error and change exit code, go to next arg
				fprintf(stderr, "no result for '%s'\n", arg);
				code = 2;
				continue;
			}
		}
		
		// If this line is reached, print out the periodic table entry that was found
		printf("%d\t%s\t%s\n", nz, symbol, name);
	}
	
	// Exit with the return code
	return code;
}

// Return whether the string is numeric (with possible leading '-')
bool is_number(char * string)
{
	// Declarations
	int i = 0;
	char c;
	
	// Negative numbers can start with a '-', skip it
	if (string[0] == '-')
		i++;
	
	// Empty strings and lone hypens are not numbers
	if (string[i] == '\0')
		return false;
	
	// Loop through the rest of the string until '\0' is encountered
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

// Change capitalization in the string to title case so it matches the lookup tables
void title_case(char * string)
{
	// Declarations
	int diff;		// Value to add to lowercase char to make it uppercase
	bool start = true;	// Whether the next alphabetic character is the start of a word
	int i = 0;
	char c;
	
	// Calculate the value of diff
	diff = 'A' - 'a';
	
	// Loop through the string until '\0' is encountered
	do
	{
		c = string[i];
		
		// If a lowercase letter is found
		if ((c >= 'a') && (c <= 'z'))
		{
			// Capitalize if it begins a word, and mark the next as not beginning a word
			if (start)
			{
				string[i] += diff;
				start = false;
			}
		}
		// If an uppercase letter is found
		else if ((c >= 'A') && (c <= 'Z'))
		{
			// If a word has started, mark the next letter as not the beginning of a word
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

