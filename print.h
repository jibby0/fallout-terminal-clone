#ifndef PRINT_H
#define PRINT_H

/// Print characters onto the screen (not player input).
/// @param arr  string to print
/// @param line  line on which to print the string
///
void slowPrint(char arr[], int line, int ybuf, int xbuf);


/// Print characters onto the screen (player input).
/// @param arr  string to print
/// @param line  line on which to print the string
///
void slowType(char arr[], int line, int ybuf, int xbuf);


/// Operates the same way as slowPrint, but cannot be interrupted 
/// by a key press.
/// @param arr  string to print
/// @param line  line on which to print the string
/// 
void passPrint(char arr[], int line, int ybuf, int xbuf);


/// Checks if a key has been pressed. Used to skip the opening sequence and
/// jump straight to pass().
///
int kbhit();


/// Used by pass() to print the left side of the screen. First prints 
/// a hexidecimal representation of an int, then the section of the 
/// string containing words and garbage.
/// @param hex  number to be displayed in hexidecimal
/// @param arr  string to be printed
/// @param line  line on which to print the string
/// @param offset  used to determine which side of the screen to print on
///
void printChoices(int hex, char arr[], int line, int offset, int ybuf, int xbuf);

#endif // PRINT_H

// end
