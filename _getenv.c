#include "header.h"

/**
 * get_index - gets index of env var in environ
 * @name: env var key to search for
 * Return: index
 */
int get_index(const char *name)
{
	int i, j;

	if (name == NULL)
		return (-1);
	for (i = 0; environ[i]; i++)
	{
		if (name[0] == environ[i][0])
		{
			for (j = 0; (name[j] == environ[i][j]) && name[j]; j++)
				;
			if (!name[j])
				break;
		}
	}
	if (environ[i] == NULL)
		return (-1);
	return (i);
}

/**
 * _getenv - gets ptr to values of an env var
 * @name: env var key to search for
 * Return: ptr to value of the env var
 */
char *_getenv(const char *name)
{
	int index = get_index(name);
	int i = 0;

	while (environ[index][i] != '=')
		i++;
	i++;
	return (&environ[index][i]);
}
