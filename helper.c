#include "header.h"

/**
 * _strcpy - copies src string to dest buffer
 * @dest: destination buffer
 * @src: source to copy to buffer
 * Return: dest ptr
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0 ; src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - concats source to destination buffer
 * @dest: destination buffer
 * @src: source to concat
 * Return: dest ptr
 */
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

/**
 * _strcmp - compares two strings
 * @s1: 1st str to compare
 * @s2: 2nd str to compare
 * Return: difference bet s1 and s2 last char
 */
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
