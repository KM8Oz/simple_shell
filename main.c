#include "shell.h"

/**
 * _split_line -split input line into args vector.
 * @line: input line.
 * Return: args vector.
 */

char **_split_line(char *line)
{
	int bufsize = _TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token, **tokens_backup;

	if (!tokens)
	{
		_putstr("./hsh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, _TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;
		if (position >= bufsize)
		{
			bufsize += _TOK_BUFSIZE;
			tokens_backup = tokens;
			tokens = _realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				free(tokens_backup);
				_putstr("./hsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, _TOK_DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * _loop - loop arround to keep promps going
 * Return: void.
 */

void _loop(void)
{
	char *line;
	char **args;
	int status;

	do {
		_putstr("$ ");
		line = _read_line();
		args = _split_line(line);
		status = _execute(args);
		free(line);
		free(args);
	} while (status);
}

/**
 * main - main function
 * @argv: args vectors
 * @argc: args count
 * Return: 0.
 */

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	_loop();
	return (EXIT_SUCCESS);
}
