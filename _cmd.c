#include "main.h"

/**
 * clearcmd - Initializes the CMD struct.
 * @cmd: Pointer to the CMD structure.
 */
void clearcmd(CMD *cmd)
{
	cmd->arg = NULL;
	cmd->argv = NULL;
	cmd->path = NULL;
	cmd->argc = 0;
}

/**
 * setcmd - Initializes the CMD struct.
 * @cmd: Pointer to the CMD structure.
 * @av: Argument vector.
 */
void setcmd(CMD *cmd, char **av)
{
	int i = 0;

	cmd->fname = av[0];
	if (cmd->arg)
	{
		cmd->argv = strtow(cmd->arg, " \t");
		if (!cmd->argv)
		{
			cmd->argv = malloc(sizeof(char *) * 2);
			if (cmd->argv)
			{
				cmd->argv[0] = _strdup(cmd->arg);
				cmd->argv[1] = NULL;
			}
		}
		for (i = 0; cmd->argv && cmd->argv[i]; i++)
			;
		cmd->argc = i;

		replace_alias(cmd);
		replace_vars(cmd);
	}
}

/**
 * freecmd - Frees CMD struct fields.
 * @cmd: Pointer to the CMD structure.
 * @all: True if freeing all fields.
 */
void freecmd(CMD *cmd, int all)
{
	ffree(cmd->argv);
	cmd->argv = NULL;
	cmd->path = NULL;
	if (all)
	{
		if (!cmd->cmd_buf)
			free(cmd->arg);
		if (cmd->env)
			free_list(&(cmd->env));
		if (cmd->history)
			free_list(&(cmd->history));
		if (cmd->alias)
			free_list(&(cmd->alias));
		ffree(cmd->environ);
		cmd->environ = NULL;
		bfree((void **)cmd->cmd_buf);
		if (cmd->readfd > 2)
			close(cmd->readfd);
		_putchar(BUF_FLUSH);
	}
}
