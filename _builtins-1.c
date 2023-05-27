#include "main.h"

/**
 * _exit0 - Exits the shell with a given exit status.
 * @cmd: Pointer to the CMD structure.
 *
 * Return: Returns 0 if cmd->argv[0] is not "exit".
 */
int _exit0(CMD *cmd)
{
	int exitStatus;

	if (cmd->argv[1])
	{
		exitStatus = _erratoi(cmd->argv[1]);
		if (exitStatus == -1)
		{
			cmd->status = 2;
			print_error(cmd, "Illegal number: ");
			_eputs(cmd->argv[1]);
			_eputchar('\n');
			return (1);
		}
		cmd->err_num = exitStatus;
		return (-2);
	}
	cmd->err_num = -1;
	return (-2);
}

/**
 * _cd - Changes the current directory of the process.
 * @cmd: Pointer to the CMD structure.
 *
 * Return: Always 0.
 */
int _cd(CMD *cmd)
{
	char *currentDir, *targetDir, buffer[1024];
	int chdir_ret;

	currentDir = getcwd(buffer, 1024);
	if (!currentDir)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!cmd->argv[1])
	{
		targetDir = _getenv(cmd, "HOME=");
		if (!targetDir)
			chdir_ret = chdir(
				(targetDir = _getenv(cmd, "PWD=")) ? targetDir : "/"
			);
		else
			chdir_ret = chdir(targetDir);
	}
	else if (_strcmp(cmd->argv[1], "-") == 0)
	{
		if (!_getenv(cmd, "OLDPWD="))
		{
			_puts(currentDir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(cmd, "OLDPWD="));
		_putchar('\n');
		chdir_ret = chdir(
			(targetDir = _getenv(cmd, "OLDPWD=")) ? targetDir : "/"
		);
	}
	else
		chdir_ret = chdir(cmd->argv[1]);
	check_chrdir(chdir_ret, cmd, buffer);
	return (0);
}

/**
 * check_chrdir - check directory changes
 * @chdir_ret: chdir return value
 * @cmd: Pointer to the CMD structure.
 * @buffer: dir buffer.
 *
 * Return: void.
 */

void check_chrdir(int chdir_ret, CMD *cmd, char buffer[1024])
{
	if (chdir_ret == -1)
	{
		print_error(cmd, "can't cd to ");
		_eputs(cmd->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv0(cmd, "OLDPWD", _getenv(cmd, "PWD="));
		_setenv0(cmd, "PWD", getcwd(buffer, 1024));
	}
}

/**
 * _help - Prints help information.
 * @cmd: Pointer to the CMD structure.
 *
 * Return: Always 0.
 */
int _help(CMD *cmd)
{
	char **arg_array;

	arg_array = cmd->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */

	return (0);
}
