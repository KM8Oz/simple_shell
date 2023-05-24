#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
extern char **environ;
typedef struct CommandNode {
    char command[100];
    struct CommandNode* next;
} CommandNode;
typedef struct CommandHistory {
    CommandNode* head;
    CommandNode* tail;
} CommandHistory;

CommandHistory* create_history();
void print_history(const CommandHistory* history);
void clear_history(CommandHistory* history);
void add_to_history(CommandHistory* history, const char* command);
int _setenv(const char *name, const char *value, int overwrite);
int _strlen(const char *f);
int _putchar(char c);
int clear_screen(void);
int switch_builtin_command(char *cmds[64]);
char *getLastDirectory(const char *path);
char *_strrealloc(char *ptr, size_t size);
char *_strcpy(char *dest, const char *src);
char *_getenv(const char *name);
int _putstr(char *c);
int _strncmp(const char *str1, const char *str2, size_t n);
char *_strchr(const char *str, int character);
char *_strdup(const char *str);
char *find_command_path(char *buffer);
int change_directory(char *path);
void run(char *buffer, CommandHistory *history);

#endif /*MAIN_H*/
