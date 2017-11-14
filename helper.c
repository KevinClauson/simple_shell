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
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i] != '\0'; ++i)
		;
	return (s1[i] - s2[i]);
}

/**
 * _strlen - returns length of a string
 * @s: input ptr to a char
 * Return: length of string
 */
int _strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}
