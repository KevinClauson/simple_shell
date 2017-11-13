#include "header.h"

int isInString(char a, char *lst)
{
	if(a == *lst)
		return 1;
	return 0;
}

char* _strtok(char *src)
{
	char *start, *end;
	static char *s_src = NULL;
	char *delims = " ";

	if(src)
		s_src = src;
	start = end = s_src;

	if (*start == '\0') /* If start equals \0 prev string was last one */
		return NULL;
	while(isInString(*end, delims)) /*check for leadin spaces */
	{
		end++;
		start++;
	}
	while(*end)
	{
		if(isInString(*end, delims))
			break;
		end++;
	}
	*end = '\0';  /* Put in null char */
	while(isInString(*(end+1), delims))
		end++;    /* check if more than one space */
	s_src = end + 1;
	return (start);
}
