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

void puts(char *string)
{
	sys_req(WRITE, COM1, string, strlen(string));
}

// Method for concatenating two strings UNTESTED
char *strcat(char *first, char *second)
{
	char result[100];
	int i = 0, k = 0;
	// insert the first string into the result
	while (strcmp(&first[i], "\0") != 0)
	{
		result[k] = first[i];
		i++;
		k++;
	}
	// Insert the second string into the result
	while (strcmp(&second[i], "\0") != 0)
	{
		result[k] = second[i];
		i++;
		k++;
	}
	result[k] = '\0';

	char *resultptr = result;
	puts(resultptr);

	return resultptr;
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
