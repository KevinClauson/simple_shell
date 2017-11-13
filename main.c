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
	size_t n = 0;
	int status;
	pid_t child_pid;
	char *line = NULL, **args, **path;

	path = parse_args(getenv("PATH"), ":");
	printf("%s\n", path[0]);
	while(1)
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
			if (execve(args[0], args, NULL) == -1)
				exit(98);
		}
		else
			wait(&status);
	}
	free(line);
	free(args);
	return (0);
}
