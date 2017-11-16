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
			break;
		num *= 10;
		num += args[1][i] - '0';
		i++;
	}
	if (args[1][i] == '\0')
		exit(num);
	return (1);
}

/**
 * print_env - prints environment
 * @args: ptr to str of args
 * Return: 0 on success, 1 otherwise
 */
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

int _unsetenv(char **args, char **my_environ)
{
	int i = get_index(args[1]);

	if (i == -1)
		return (-1);
	free(my_environ[i]);
	while (my_environ[i])
	{
		my_environ[i] = my_environ[i + 1];
		i++;
	}
	return (0);
}
/**
 * my_cd - changes directory
 * @args: ptr to str of args
 * Return: 0 success, 2 on error
 */
int my_cd(char **args)
{
	if (args[1] == NULL)
		return (chdir(_getenv("HOME")));
	if (chdir(args[1]) == -1)
	{
		perror("cd");
		return (2);
	}
	return (0);
}
/*
int _setenv(char **args)
{
	char *buffer;
	int i = get_index(args[1]);

	if (i >= 0 && args[3])
	{
		buffer = malloc((_strlen(args[1]) + _strlen(args[2]) + 2));
		_strcpy(buffer, args[1]);
		_strcat(buffer, "=");
		_strcat(buffer, args[2]);
		printf("%s\n", buffer);
	}
	return (0);
}
*/
