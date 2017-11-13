#include "header.h"

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

char *_getenv(const char *name)
{
	int index = get_index(name);
	int i = 0;

	while (environ[index][i] != '=')
		i++;
	i++;
	return (&environ[index][i]);
}

int main(void)
{
	char *buffer = _getenv("PATH");
	printf("%s\n", buffer);
	return (0);
}
