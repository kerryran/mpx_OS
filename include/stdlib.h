#ifndef MPX_STDLIB_H
#define MPX_STDLIB_H

/**
 @file stdlib.h
 @brief A subset of standard C library functions.
*/

/**
 Convert an ASCII string to an integer
 @param s A NUL-terminated string
 @return The value of the string converted to an integer
*/
int atoi(const char *s);

/**
 Convert an integer to an ASCII string
 @param num The value of the integer converted to a string
 @param base The base for number conversion (decimal, hex, or binary)
 @param string The value that holds the converted string
*/
char* itoa(int num, char* string, int base);

/**
 Reverses the order of a string
 @param string The string value that needs to be reversed
 @param num The length of the string 
*/
void reverse(char string[], int len);
#endif
