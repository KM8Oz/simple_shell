#include "main.h"

/**
 * loop - Main shell loop.
 * @cmd: Pointer to the CMD structure.
 * @av: Argument vector from main().
 *
 * Return: 0 on success, 1 on error or error code.
 */
int loop(CMD *cmd, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clearcmd(cmd);
		if (interactive(cmd))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(cmd);
		if (r != -1)
		{
			setcmd(cmd, av);
			builtin_ret = _builtin(cmd);
			if (builtin_ret == -1)
				_cmd(cmd);
		}
		else if (interactive(cmd))
			_putchar('\n');
		freecmd(cmd, 0);
	}
	write_history(cmd);
	freecmd(cmd, 1);
	if (!interactive(cmd) && cmd->status)
		exit(cmd->status);
	if (builtin_ret == -2)
	{
		if (cmd->err_num == -1)
			exit(cmd->status);
		exit(cmd->err_num);
	}
	return (builtin_ret);
}

/**
 * _fpath - finds this cmd in the PATH string
 * @cmd: the info struct
 * @pathstr: the PATH string
 * @ptf: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *_fpath(CMD *cmd, char *pathstr, char *ptf)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(ptf) > 2) && starts_with(ptf, "./"))
	{
		if (is_cmd(cmd, ptf))
			return (ptf);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = _dupstr(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, ptf);
			else
			{
				_strcat(path, "/");
				_strcat(path, ptf);
			}
			if (is_cmd(cmd, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * _cmd - Finds a command in PATH.
 * @cmd: Pointer to the CMD structure.
 *
 * Return: void
 */
void _cmd(CMD *cmd)
{
	char *path = NULL;
	int i, k;

	cmd->path = cmd->argv[0];
	if (cmd->linecount_flag == 1)
	{
		cmd->line_count++;
		cmd->linecount_flag = 0;
	}
	for (i = 0, k = 0; cmd->arg[i]; i++)
	{
		if (!is_delim(cmd->arg[i], " \t\n"))
			k++;
	}
	if (!k)
		return;
	path = _fpath(cmd, _getenv(cmd, "PATH="), cmd->argv[0]);
	_fork_path(path, cmd);
}
/**
 * _builtin - Finds a builtin command.
 * @cmd: Pointer to the CMD structure.
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * -2 if builtin signals exit().
 */
int _builtin(CMD *cmd)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _exit0},
		{"env", _print_env},
		{"help", _help},
		{"history", print_history},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", _cd},
		{NULL, NULL}};

	for (i = 0; builtintbl[i].type; i++)
	{
		if (_strcmp(cmd->argv[0], builtintbl[i].type) == 0)
		{
			cmd->line_count++;
			built_in_ret = builtintbl[i].func(cmd);
			break;
		}
	}
	return (built_in_ret);
}
