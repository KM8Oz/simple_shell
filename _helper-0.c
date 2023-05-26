#include "shell.h"

/**
 * _builtins - return the size if builtins
 * Return: size.
 */

int _builtins(void)
{
	char *built_in_string[] = {"cd", "help", "exit", "clear", "env"};

	return (sizeof(built_in_string) / sizeof(char *));
}

/**
 * _cd - builtin cd function
 * @args: args vectors
 * Return: 0.
 */

int _cd(char **args)
{
	if (args[1] == NULL)
		_putstr("expected argument to cd \n");
	else if (chdir(args[1]) != 0)
		perror("./hsh");
	return (1);
}

/**
 * _help - builtin help function
 * @args: args vectors
 * Return: 0.
 */

int _help(char **args)
{
	int i;
	char *built_in_string[] = {"cd", "help", "exit", "clear", "env"};
	(void)args;

	_putstr("This is simple C shell build by @kmoz\n");
	_putstr("Type program names and arguments, and hit enter.\n");
	_putstr("The following are built in:\n");
	for (i = 0; i < _builtins(); i++)
		_putstr(built_in_string[i]);
	_putstr("Use the man command for information on other programs.\n");
	return (1);
}

/**
 * _exit2 - builtin exit function
 * @args: args vectors
 * Return: 0.
 */

int _exit2(char **args)
{
	(void)args;
	return (0);
}

/**
 * _launch - execute command in stdin
 * @args: args vectors
 * Return: 0 or 1.
 */

int _launch(char **args)
{
	pid_t pid = -1;
	int status;
	char *path = NULL;

	path =  find_command_path(args[0]);
	if (access(path, F_OK) != -1)
	{
		pid = fork();
	}
	if (pid == 0)
	{

		if (execve(path, args, environ) == -1)
			perror("./hsh");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("./hsh");
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}
