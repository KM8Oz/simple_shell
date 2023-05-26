#ifndef MAIN_H
#define MAIN_H
#define _TOK_BUFSIZE 64
#define _TOK_DELIM " \t\r\n\a"
#define _RL_BUFSIZE 1024
#define BUFFER_SIZE 1024

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern char **environ;

/**
 * struct ENV - simple envirenment variable details
 * Struct.
 * @index: envirenment variable index
 * @key: envirenment variable key
 * @value: envirenment variable value
 * Description: simple envirenment variable details structure
 */

typedef struct ENV
{
	int index;
	char *key;
	char *value;
} ENV;
char *join_strings(const char **strings, int count);
int _cd(char **args);
void *_realloc(void *ptr, size_t size);
char *_strcpy(char *dest, const char *src);
int _help(char **args);
char *_getenv0(const char *name);
int _exit2(char **args);
char *_read_line(void);
int _putchar(char c);
char *find_command_path(char *buffer);
int print_environment(char **args);
int _putstr(char *c);
ENV *_getenv(char *key);
int clear_screen(char **args);
int _strlen(const char *f);
int _execute(char **args);
int _builtins(void);
char *_strdup(const char *str);
char *_strchr(const char *str, int character);
int _strncmp(const char *str1, const char *str2, size_t n);
int _launch(char **args);
char **_split_line(char *line);
void _loop(void);
#endif /*MAIN_H*/
