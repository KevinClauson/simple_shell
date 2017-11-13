#include "header.h"

char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0 ; src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
char *_strcat(char *dest, char *src)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
				;
	for (j = 0; src[j] != '\0'; j++)
		dest[i + j] = src[j];
	dest[i + j] = '\0';
	return (dest);
}
