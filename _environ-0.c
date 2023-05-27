#include "main.h"

/**
 * _print_env - Prints the current environment.
 * @cmd: Pointer to the CMD structure.
 * Return: Always 0.
 */
int _print_env(CMD *cmd)
{
	print_list_str(cmd->env);
	return (0);
}

/**
 * _getenv - Gets the value of an environment variable.
 * @cmd: Pointer to the CMD structure.
 * @name: Name of the environment variable.
 * Return: The value of the environment variable.
 */
char *_getenv(CMD *cmd, const char *name)
{
	list_t *node = cmd->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _setenv - Initializes a new environment variable
 * or modifies an existing one.
 * @cmd: Pointer to the CMD structure.
 * Return: Always 0.
 */
int _setenv(CMD *cmd)
{
	if (cmd->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv0(cmd, cmd->argv[1], cmd->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetenv - Removes an environment variable.
 * @cmd: Pointer to the CMD structure.
 * Return: Always 0.
 */
int _unsetenv(CMD *cmd)
{
	int i;

	if (cmd->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= cmd->argc; i++)
		_unsetenv0(cmd, cmd->argv[i]);

	return (0);
}

/**
 * _add_env_list - Populates the environment linked list.
 * @cmd: Pointer to the CMD structure.
 * Return: Always 0.
 */
int _add_env_list(CMD *cmd)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	cmd->env = node;
	return (0);
}
