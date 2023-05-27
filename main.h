#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_STAR \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
* struct cmd - contains pseudo-arguments to pass into a function,
* allowing a uniform prototype for a function pointer struct
* @arg: a string generated from getline containing arguments
* @argv: an array of strings generated from arg
* @path: a string representing the current command's path
* @argc: the argument count
* @line_count: the error count
* @err_num: the error code for exit()
* @linecount_flag: a flag indicating whether to count this line of input
* @fname: the program filename
* @env: linked list, a local copy of environ
* @environ: a custom modified copy of environ from the linked list env
* @history: the history node
* @alias: the alias node
* @env_changed: a flag indicating whether environ was changed
* @status: the return status of the last executed command
* @cmd_buf: address of pointer to cmd_buf, a flag indicating chaining
* @cmd_buf_type: CMD_type (||, &&, ;)
* @readfd: the file descriptor from which to read line input
* @histcount: the history line number count
*/

typedef struct cmd
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} CMD;

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(CMD *);
} builtin_table;

int check_if_file_exist(int *fileid, CMD *cmd, int argc, char **argv);

int loop(CMD *a, char **b);
int _builtin(CMD *a);
void _cmd(CMD *a);
void _fcmd(CMD *a);
int process_buffer(CMD *cmd, char *buf, ssize_t size);

int if_exist(CMD *a, char *b);
char *_dupstr(const char *a, int b, int c);
char *_fpath(CMD *a, char *b, char *c);

void _eputs(char *a);
int _eputchar(char a);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int is_cmd(CMD *cmd, char *path);

int _strlen(char *a);
int _strcmp(char *a, char *b);
char *starts_with(const char *a, const char *b);
char *_strcat(char *b, char *a);

char *_strcpy(char *a, char *b);
char *_strdup(const char *a);
void _puts(char *a);
int _putchar(char a);
void _fork_path(char *path, CMD *cmd);

char *_strncpy(char *a, char *b, int c);
char *_strncat(char *a, char *v, int c);
char *_strchr(char *a, char v);

char **strtow(char *v, char *a);
char **strtow2(char *v, char a);

char *_memset(char *, char v, unsigned int);
void ffree(char **a);
void *_realloc(void *a, unsigned int, unsigned int);

int bfree(void **a);

int interactive(CMD *a);
int is_delim(char a, char *b);
int _isalpha(int a);
int _atoi(char *c);

int _erratoi(char *a);
void print_error(CMD *a, char *b);
int print_d(int a, int b);
char *convert_number(long int, int a, int b);
void remove_comments(char *a);

int _exit0(CMD *a);
int _cd(CMD *a);
int _help(CMD *a);
void check_chrdir(int chdir_ret, CMD *cmd, char buffer[1024]);

int print_history(CMD *a);

ssize_t get_input(CMD *a);
int _getline(CMD *a, char **b, size_t *c);
void sigintHandler(int a);

void clearcmd(CMD *a);
void setcmd(CMD *a, char **b);
void freecmd(CMD *a, int b);

char *_getenv(CMD *a, const char *b);
int _print_env(CMD *a);
int _setenv(CMD *a);
int _unsetenv(CMD *a);
int _add_env_list(CMD *a);

char **_get_environ(CMD *a);
int _unsetenv0(CMD *a, char *b);
int _setenv0(CMD *a, char *b, char *c);

char *get_old_file(CMD *cmd);
int write_history(CMD *cmd);
int read_history(CMD *cmd);
int build_history_list(CMD *cmd, char *buf, int linecount);
int renumber_history(CMD *cmd);

list_t *add_node(list_t **a, const char *b, int c);
list_t *add_node_end(list_t **a, const char *b, int c);
size_t print_list_str(const list_t *a);
int delete_node_at_index(list_t **a, unsigned int);
void free_list(list_t **a);

size_t list_len(const list_t *a);
char **list_to_strings(list_t *a);
size_t print_list(const list_t *a);
list_t *node_starts_with(list_t *a, char *b, char c);
ssize_t get_node_index(list_t *a, list_t *b);

int is_chain(CMD *a, char *b, size_t *c);
void check_chain(CMD *a, char *b, size_t *c, size_t d, size_t e);
int replace_alias(CMD *a);
int replace_vars(CMD *a);
int replace_string(char **old, char *new);

#endif
