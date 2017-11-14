#include "header.h"

/**
 * my_exit - exits shell
 * @args: ptr to str of args
 * Return: -1 if args[0] NULL, exits 0 otherwise
 */
int my_exit(char **args)
{
	int num = 0, i = 0;

	if (args[1] == NULL)
		exit(0);
	while (args[1][i])
	{
		if (!(args[1][i] >= '0' && args[1][i] <= '9'))
		{
			break;
		}
		num *= 10;
		num += args[1][i] - '0';
		i++;
	}
	if (args[1][i] == '\0')
		exit(num);
	return (1);
}

int print_env(char **args)
{
	size_t i;
	char **env_aux;
	char *cnt;

	if (args[0] == NULL)
		return (1);
	for (env_aux = environ; *env_aux != NULL; env_aux++)
	{
		cnt = *env_aux;
		i = 0;
		while (*cnt)
		{
			++cnt;
			++i;
		}
		write(STDOUT_FILENO, *env_aux, i);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
