#include "main.h"

/**
 * _get_environ - Returns a copy of the
 * string array
 * containing the environment variables.
 * @cmd: Pointer to the CMD structure.
 * Return: The string array copy of the
 * environment variables.
 */
char **_get_environ(CMD *cmd)
{
	if (!cmd->environ || cmd->env_changed)
	{
		cmd->environ = list_to_strings(cmd->env);
		cmd->env_changed = 0;
	}

	return (cmd->environ);
}

/**
 * _unsetenv0 - Removes an environment variable.
 * @cmd: Pointer to the CMD structure.
 * @var: The name of the environment variable
 * to remove.
 * Return: 1 if the environment variable was
 * successfully
 * removed, 0 otherwise.
 */
int _unsetenv0(CMD *cmd, char *var)
{
	list_t *node = cmd->env;
	size_t k = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			cmd->env_changed = delete_node_at_index(&(cmd->env), k);
			k = 0;
			node = cmd->env;
			continue;
		}
		node = node->next;
		k++;
	}
	return (cmd->env_changed);
}

/**
 * _setenv0 - Initializes a new environment variable
 * or modifies an existing one.
 * @cmd: Pointer to the CMD structure.
 * @var: The name of the environment variable.
 * @value: The value of the environment variable.
 * Return: Always 0.
 */
int _setenv0(CMD *cmd, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = cmd->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			cmd->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(cmd->env), buf, 0);
	free(buf);
	cmd->env_changed = 1;
	return (0);
}
