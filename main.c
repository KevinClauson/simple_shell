#include "header.h"
/**
 *
 */
char **parse_args(char *line, char *delim)
{
	size_t len = BUFF_SIZE, i = 0;
	char *token;
	char **args = malloc(len * sizeof(char *));

	if (args == NULL || line == NULL)
		exit(EXIT_FAILURE);
	token = strtok(line, delim);
	
	while (token != NULL)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, delim);
	}
	args[i] = NULL;
	if (_strcmp(args[0], "exit") == 0)
		exit(98);
	return (args);
}

int check_slash(char *arg)
{
	int i = 0;

	while (arg[i])
	{
		if (arg[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int main(void)
{
	ssize_t bytes;
	size_t n = 0, i = 0;
	int status;
	pid_t child_pid;
	char *line = NULL, **args, **path, buffer_path[BUFF_SIZE];

	path = parse_args(_getenv("PATH"), ":");
	while (1)
	{
		_getprompt();
		bytes = getline(&line, &n, stdin);
		if (bytes == EOF)
			break;
		args = parse_args(line, " \n\t");
		child_pid = fork();
		if (child_pid == -1)
			perror("ERROR");
		if (child_pid == 0)
		{
			/*if (_strcmp(args[0], "env"))
			{
				while (environ[i])
				{
					write(1, environ[i], _strlen(environ[i]));
					i++;
				}
			}
			else*/ if (check_slash(args[0]))
			{
				if (execve(args[0], args, NULL) == -1)
					exit(98);
			}
			else
			{
				while (path[i])
				{
					_strcpy(buffer_path, path[i]);
					_strcat(buffer_path, "/");
					_strcat(buffer_path, args[0]);
					if (execve(buffer_path, args, NULL) != -1)
						break;
					i++;
				}
			}
				/* check path */	
		}
		else
			wait(&status);
	}
	free(path);
	free(line);
	free(args);
	return (0);
}
