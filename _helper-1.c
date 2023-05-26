#include "shell.h"

/**
 * _execute - execute args
 * @args: args vectors
 * Return: 0 or 1.
 */

int _execute(char **args)
{
	int i;
	char *built_in_string[] = {"cd", "help", "exit", "clear", "env"};

	int (*built_in_function[])(char **) = {
		&_cd, &_help, &_exit2, &clear_screen, &print_environment
	};
	if (args[0] == NULL)
		return (1);
	for (i = 0; i < _builtins(); i++)
		if (strcmp(args[0], built_in_string[i]) == 0)
			return ((*built_in_function[i])(args));

	return (_launch(args));
}

/**
 * _read_line - read user input line
 * Return: string pointer.
 */

char *_read_line(void)
{
	int bufsize = _RL_BUFSIZE;
	int position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	int c;

	if (!buffer)
	{
		fprintf(stderr, "allocation error\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		c = getchar();
		if (c == EOF)
			exit(EXIT_SUCCESS);
		else if (c == '\n')
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else
		{
			buffer[position] = c;
		}
		position++;
		if (position >= bufsize)
		{
			bufsize += _RL_BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
			{
				fprintf(stderr, "allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

/**
 * _putchar - print char in stdout
 * @c: one char
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _putstr - print str in stdout
 * @c: char*
 *
 * Return: ...
 */

int _putstr(char *c)
{
	int i = 0;

	if (c == NULL)
		return (0UL);
	while (*(c + i))
	{
		_putchar(*(c + i));
		i++;
	}

	return (sizeof(char) * _strlen(c));
}
