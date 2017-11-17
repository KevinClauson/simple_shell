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
	token = strtok(line, delim);
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
		token = strtok(NULL, delim);
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
int check_builtin(char **args)/*, char **my_environ)*/
{
	int i = 0;
	builtin_t built_func[] = {
		{"exit", my_exit},
		{"cd", my_cd},
		{"env", print_env},
		{"unsetenv", _unsetenv},
		{"setenv", _setenv},
		{NULL, NULL}
	};

	while (built_func[i].str != NULL)
	{
		if (_strcmp(args[0], built_func[i].str) == 0)
			return (built_func[i].f(args));/*, my_environ));*/
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
	int i = 0;
	size_t path_space = 31, len = _strlen(args[0]) + path_space + 1;
	char *buffer_path;

	if (check_slash(args[0]))
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("execve");
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
			if ((_strlen(path[i])) >= path_space)
			{
				buffer_path = _realloc(buffer_path, len, _strlen(path[i]));
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
			perror("path");
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * main - shell program
 * Return: 0
 */
int main(void)
{
	int test, status;
	pid_t child_pid;
	ssize_t bytes;
	size_t n = 0, i = 0;
	char *line = NULL, **args, **path, **my_env = create_env(), *path_val = NULL;

	environ = my_env;
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
		path_val = copy_path();
		path = parse_args(path_val, ":\n");
		test = check_builtin(args);
		if (test == -1)
		{
			child_pid = fork();
			if (child_pid == -1)
				perror("fork");
			if (child_pid == 0)
				exec_fn(args, path);
			else
				wait(&status);
		}
		free(args), free(path_val), free(path);
	}
	free(line), free_env(my_env);
	return (0);
}
