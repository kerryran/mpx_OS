#include <stdlib.h>
#include <ctype.h>


int atoi(const char *s)
{
	int res = 0;
	char sign = ' ';

	while (isspace(*s)) {
		s++;
	}

	if (*s == '-' || *s == '+') {
		sign = *s;
		s++;
	}

	while ('0' <= *s && *s <= '9') {
		res = res * 10 + (*s - '0');
		s++;

	}

	if (sign == '-') {
		res = res * -1;
	}

	return res;
}
char* itoa (int num, char* string, int base)
{
	int i = 0;

	//handles 0 or empty string is printed
	if(num == 0){
		string[i++] = '0';
		string[i] = '\0';

		return string;
	}

	//proceed for regular numbers
	while (num != 0){
		int remainder = num % base;

		string[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
		num = num / base;
	}

	//append null terminator
	string[i] = '\0';

	//reverse string
	reverse(string, i);

	return string;
}
void reverse(char string[], int len)
{
	int start = 0;
	int end = len - 1;

	while(start < end){
		char temp = string[start];
		string[start] = string [end];
		string[end] = temp;
		end--;
		start++;
	}
}
