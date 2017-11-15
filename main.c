#include "header.h"

/**
 * parse_args - parse args as strings, store in buffer
 * @line: user input
 * @delim: set delimiter
 * Return: ptr to strings of args
 */
char **parse_args(char *line, char *delim)
{
	size_t i = 0, len = BUFF_SIZE, new_size;
	char *token;
	char **args = malloc(len * sizeof(char *));

	if (args == NULL || line == NULL)
		exit(EXIT_FAILURE);
	token = my_strtok(line, delim);
	while (token != NULL)
	{
		args[i] = token;
		i++;
		if (i >= len)
		{
			new_size = len * 2;
			args = _realloc(args, len * sizeof(char *), new_size * sizeof(char *));
			if (args == NULL)
				exit(EXIT_FAILURE);
			len = new_size;
		}
		token = my_strtok(NULL, delim);
	}
	args[i] = NULL;
	return (args);
}

/**
 * check_slash - checks if arg has slash char
 * @arg: ptr to an arg
 * Return: 1 if args has slash, 0 otherwise
 */
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

/**
 * check_builtin - check if arg is builtin fn
 * @args: ptr to str of args
 * Return: index of the cmd, or 0 if not found
 */
int check_builtin(char **args)
{
	int i = 0;
	builtin_t built_func[] = {
		{"exit", my_exit},
		{"env", print_env},
		{"unsetenv", _unsetenv},
		/* {"setenv", _setenv}, */
		{NULL, NULL}
	};

	while (built_func[i].str != NULL)
	{
		if (_strcmp(args[0], built_func[i].str) == 0)
		{
			return (built_func[i].f(args));
		}
		i++;
	}
	return (-1);
}

/**
 * exec_fn - execs cmd in path, or exit if failure
 * @args: parsed args buffer
 * @path: parsed buffer of path
 */
void exec_fn(char **args, char **path)
{
	pid_t child_pid;
	int i = 0, status;
	size_t len = _strlen(args[0]) + 32, n;
	char *buffer_path;

	child_pid = fork();
	if (child_pid == -1)
		perror("ERROR");
	if (child_pid == 0)
	{
		if (check_slash(args[0]))
		{
			if (execve(args[0], args, NULL) == -1)
			{
				perror("ERROR");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			buffer_path = malloc(len * sizeof(char)); 
			if (buffer_path == NULL)
				exit(EXIT_FAILURE);
			while (path[i])
			{
				if ((n = _strlen(path[i])) >= 31)
				{
					buffer_path = _realloc(buffer_path, len, n);
					if (buffer_path == NULL)
						exit(EXIT_FAILURE);
				}
				_strcpy(buffer_path, path[i]);
				_strcat(buffer_path, "/");
				_strcat(buffer_path, args[0]);
				if (execve(buffer_path, args, NULL) != -1)
					break;
				i++;
			}
			free(buffer_path);
			if (path[i] == NULL)
			{
				perror("ERROR");
				exit(EXIT_FAILURE);
			}
		}
	}
	else
		wait(&status);
}

/**
 * main - shell program
 * Return: 0
 */
int main(void)
{
	int test;
	ssize_t bytes;
	size_t n = 0, i = 0;
	char *line = NULL, **args, **path;

	path = parse_args(_getenv("PATH"), ":");
	while (1)
	{
		signal(SIGINT, sig_handler);
		_getprompt();
		bytes = getline(&line, &n, stdin);
		if (bytes == EOF)
			break;
		for (i = 0; line[i]; i++)
		{
			if (line[i] == '#')
			{
				line[i] = '\0';
				break;
			}
		}
		args = parse_args(line, "\n \t");
		test = check_builtin(args);
		if (test == -1)
			exec_fn(args, path);
		free(args);
	}
	free(path);
	free(line);
	return (0);
}
