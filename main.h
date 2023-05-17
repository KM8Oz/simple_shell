#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 512
char *args[MAX_ARGS];
void split(const char *cmd);
void execute_cd();
void execute_command(int input, int first, int last);
void handle_child_process(int input, int last, int pipettes[2]);
void handle_parent_process(int input, int last, int status);
int run(const char *cmd, int input, int first, int last);
#endif
