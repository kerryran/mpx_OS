#include <string.h>
#include <../include/sys_req.h>

/* memcpy() and memset() are in core.c */

int strcmp(const char *s1, const char *s2)
{

	// Remarks:
	// 1) If we made it to the end of both strings (i. e. our pointer points to a
	//    '\0' character), the function will return 0
	// 2) If we didn't make it to the end of both strings, the function will
	//    return the difference of the characters at the first index of
	//    indifference.
	while ((*s1) && (*s1 == *s2))
	{
		++s1;
		++s2;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

size_t strlen(const char *s)
{
	size_t len = 0;
	while (*s++)
	{
		len++;
	}
	return len;
}

char *strtok(char *restrict s1, const char *restrict s2)
{
	static char *tok_tmp = NULL;
	const char *p = s2;

	// new string
	if (s1 != NULL)
	{
		tok_tmp = s1;
	}
	// old string cont'd
	else
	{
		if (tok_tmp == NULL)
		{
			return NULL;
		}
		s1 = tok_tmp;
	}

	// skip leading s2 characters
	while (*p && *s1)
	{
		if (*s1 == *p)
		{
			++s1;
			p = s2;
			continue;
		}
		++p;
	}

	// no more to parse
	if (!*s1)
	{
		return (tok_tmp = NULL);
	}
	// skip non-s2 characters
	tok_tmp = s1;
	while (*tok_tmp)
	{
		p = s2;
		while (*p)
		{
			if (*tok_tmp == *p++)
			{
				*tok_tmp++ = '\0';
				return s1;
			}
		}
		++tok_tmp;
	}

	// end of string
	tok_tmp = NULL;
	return s1;
}

// Method for printing to console
#define ANSI_COLOR_RED     "\x1B[31m"
#define ANSI_COLOR_GREEN   "\x1B[32m"
#define ANSI_COLOR_YELLOW  "\x1B[33m"
#define ANSI_COLOR_RESET   "\x1B[0m"
#define ANSI_COLOR_BLUE   "\x1B[34m"

// Function to write a string with specified color to the COM port
void puts_color(char *string, const char *color) {
    // Set the text color using ANSI escape codes
    sys_req(WRITE, COM1, color, strlen(color));
    sys_req(WRITE, COM1, string, strlen(string));
    // Reset the text color using ANSI escape codes
    sys_req(WRITE, COM1, ANSI_COLOR_RESET, strlen(ANSI_COLOR_RESET));
}
void puts(char *string)
{
	puts_color(string, ANSI_COLOR_GREEN);
}
void puts_cursor(char *string)
{
	puts_color(string, ANSI_COLOR_RESET );
}

// Method for concatenating two strings
char *strcat(char *first, char *second)
{
	// int to iterate through indexes of strings
	int i;

	// int with the value of the length of the first string
	int j = strlen(first);

	// iterate through the second string until the null terminator
	for (i = 0; second[i] != '\0'; i++)
	{

		// add the chars, from the second string, one at a time to the first string
		first[i + j] = second[i];
	}

	// add the null terminator
	first[i + j] = '\0';

	// return the combined strings
	return first;
}

// Method to get a substring from a char array
char *substring(char string[], int index, int length)
{
	char result[50];
	int count = 0;

	while (count < length)
	{
		result[count] = string[index + count];
		count++;
	}
	result[count] = '\0';
	char *resultptr = result;
	// Debugging
	puts("\nsubstring result: ");
	puts(resultptr);
	puts("\n");

	return resultptr;
}

int isNum(char buffer[])
{

	for (int index = 0; buffer[index] != '\0'; index++)
	{
		// Not a number
		if (buffer[index] < 48 || buffer[index] > 57)
		{
			return 0;
		}
	}
	return 1;
}
