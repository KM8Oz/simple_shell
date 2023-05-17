#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 512

static char *args[MAX_ARGS];
/**
 * split - Splits a command into individual arguments.
 * @cmd: Command string to be split.
 */
static void split(const char *cmd)
{
const char *whitespace = " \t\n";
char *temp = strdup(cmd);
int i = 0;
char *token = strtok(temp, whitespace);

while (token != NULL && i < MAX_ARGS - 1)
{
args[i] = token;
++i;
token = strtok(NULL, whitespace);
}
args[i] = NULL;
free(temp);
}

/**
 * execute_command - Executes a command with optional input and output redirection.
 * @input: Input file descriptor.
 * @first: Flag indicating if it's the first command in a pipe sequence.
 * @last: Flag indicating if it's the last command in a pipe sequence.
 */
static void execute_command(int input, int first, int last)
{
pid_t pid;
int status;
int pipettes[2];

if (args[0] != NULL)
{
if (strcmp(args[0], "exit") == 0)
{
exit(0);
}
else if (strcmp(args[0], "cd") == 0)
{
execute_cd();
return;
}
else
{
pid = fork();
if (pid == -1)
{
perror("fork");
return;
}
else if (pid == 0)
{
handle_child_process(input, last, pipettes);
}
else
{
handle_parent_process(input, last, status);
}
}
}
}

/**
 * execute_cd - Executes the 'cd' command to change directory.
 */
static void execute_cd()
{
if (args[1] != NULL)
{
if (chdir(args[1]) != 0)
{
perror("cd");
}
}
else
{
fprintf(stderr, "cd: missing directory\n");
}
}

/**
 * handle_child_process - Handles the child process execution.
 * @input: Input file descriptor.
 * @last: Flag indicating if it's the last command in a pipe sequence.
 * @pipettes: Array to hold pipe file descriptors.
 */
static void handle_child_process(int input, int last, int pipettes[2])
{
if (input != 0)
{
dup2(input, STDIN_FILENO);
close(input);
}
if (last == 0)
{
if (pipe(pipettes) == -1)
{
perror("pipe");
_exit(EXIT_FAILURE);
}
dup2(pipettes[1], STDOUT_FILENO);
close(pipettes[1]);
close(pipettes[0]);
}
if (execvp(args[0], args) == -1)
{
perror("execvp");
_exit(EXIT_FAILURE);
}
}

/**
 * handle_parent_process - Handles the parent process after the child process execution.
 * @input: Input file descriptor.
 * @last: Flag indicating if it's the last command in a pipe sequence.
 * @status: Exit status of the child process.
 */
static void handle_parent_process(int input, int last, int status)
{
if (input != 0)
close(input);
if (last == 0)
{
close(STDOUT_FILENO);
}
waitpid(pid, &status, 0);
if (WIFEXITED(status))
{
return (WEXITSTATUS(status));
}
else
{
fprintf(stderr, "Command did not exit normally\n");
return (-1);
}
}

/**
 * run - Executes a command with optional input and output redirection.
 * @cmd: Command to be executed.
 * @input: Input file descriptor.
 * @first: Flag indicating if it's the first command in a pipe sequence.
 * @last: Flag indicating if it's the last command in a pipe sequence.
 * Return: File descriptor of the command's output.
 */
static int run(const char *cmd, int input, int first, int last)
{
(void)first;
split(cmd);
execute_command(input, first, last);
return (0);
}

int main(void)
{
char line[1024];
int input;
int first;
char *cmd;
char *next;

printf("SIMPLE SHELL: Type 'exit' or send EOF to exit.\n");
while (1)
{
printf("$> ");
fflush(NULL);
if (!fgets(line, sizeof(line), stdin))
return (0);
input = 0;
first = 1;
cmd = line;
next = strchr(cmd, '|');
while (next != NULL)
{
*next = '\0';
input = run(cmd, input, first, 0);
cmd = next + 1;
next = strchr(cmd, '|');
first = 0;
}
input = run(cmd, input, first, 1);
}

return (0);
}
