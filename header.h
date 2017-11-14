#ifndef HEADER_SHELL
#define HEADER_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

/* global variables */
extern char **environ;

/* Macros */
#define BUFF_SIZE 1024

/* print prompt, getline and tokenize */
void _getprompt(void);
/* char* _strtok(char *src) */
ssize_t _getline(char *buff);
char *_strcpy(char *dest, char *src);
char *_getenv(const char *name);
int get_index(const char *name);
char *_strcat(char *dest, char *src);
int check_slash(char *arg);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
#endif
