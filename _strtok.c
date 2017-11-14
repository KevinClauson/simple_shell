#include "header.h"

int isInString(char a, char *lst) {
	while(*lst) {
		if(a == *lst++)
			return (1);
	}
	return (0);
}

char* my_strtok(char *src, const char *delims) {
	static char *s_src = NULL;

	if(src)
		s_src = src;

	char *start = s_src;
	char *end = s_src;

	if(*start == '\0')
		return NULL;
	while(isInString(*end, delims))
	{
		end++;
		start++;
	}
	while(*end != '\0' && *end != '\n')
	{
		if(isInString(*end, delims))
			break;
		end++;
	}
	*end = '\0';
	while(isInString(*(end+1), delims))
		end++;

	s_src = end + 1;

	return (start);
}
