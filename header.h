#ifndef HEADER_SHELL
#define HEADER_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

/* Macros */
#define BUFF_SIZE 1024


/* print prompt, getline and tokenize */
void _getprompt(void);
char* _strtok(char *src);
ssize_t _getline(char *buff);

#endif
