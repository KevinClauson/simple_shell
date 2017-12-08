Simple Shell: *a shell that handles simple commands*
====================================================
## By ``Kevin Clauson`` and ``Lance Wong``

### Description
``Simple Shell`` is a program that reads from the standard input and tries to interpret the user input as commands.

### How it works
When a user types a command and presses enter, the command is read to the standard input. ``Simple shell`` tokenizes the line entered. To determine if the arguments are valid commands, the program first searches its built-in commands. If it is a built-in command, the shell executes that command. Otherwise, the program check every directory in PATH and attempt to execute a command given a directory and a user command. Blog post: [How Does a Shell Work?](https://lancesanity.github.io/blog/Shell-Project)

### How to compile
`gcc -Wall -Werror -Wextra -pedantic *.c -o hsh`. To execute the program, `./hsh` and `Enter`.

### Usage
``Simple shell`` will first prompt the user for input. Once you type a command such as ``ls`` and press Enter, the program will determine if it is a valid command and either produce the desired output or an error message.

### Description of files
| File | Description |
| --- | --- |
| main.c | Main shell program with functions to parse arguments, check builtins, and execute commands  |
| prompt.c | Function to print a prompt |
| print_error.c | Function to print error messages |
| helper.c | Functions: `strcpy()`, `strcat()`, `strcmp()` and `strlen()`, and a signal handler `sig_handler()` |
| helper2.c | More helper functions: `realloc()`, `create_env()`, `free_env()`, `copy_path()`, `check_comment` |
| builtins.c | Built-in functions for `exit`, `printenv`, `unsetenv`, `cd`, `setenv` |
| getenv.c | Function: `getenv()` - gets the values for an environment variable |
| strtok.c | Function: `strtok()` - tokenizes a string given a delimiter |
| header.h | Header file with function prototypes, headers, global variables, macros, and structs |

### Allowed functions and system calls
`access` `chdir` `close` `closedir` `execve` `exit` `fork` `free` `stat` `lstat` `fstat` `getcwd` `getline` `kill` `malloc`
`open` `opendir` `perror` `read` `readdir` `signal` `strtok` `wait` `waitpid` `wait3` `wait4` `write` `_exit` `isatty` `fflush`

### How this executes commands from PATH
Since we were limited to `execve()`, we needed to find a way to search PATH if the executable's directory was not given by the user (as opposed to `execvr` which searches PATH for you). Our method is to try the command with every directory until a command was successfully executed. If the command wasn't executed, it doesn't exist within the PATH directories.
