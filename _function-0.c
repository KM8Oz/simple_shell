#include "main.h"
/**
 * _fork_path - forks a path using cmd info
 * @path: Pointer to Path string.
 * @cmd: Pointer to the CMD structure.
 * Return: void
 */

void _fork_path(char *path, CMD *cmd)
{
	if (path)
	{
		cmd->path = path;
		_fcmd(cmd);
	}
	else
	{
		if ((interactive(cmd) || _getenv(cmd, "PATH=") ||
			 cmd->argv[0][0] == '/') &&
			if_exist(cmd, cmd->argv[0]))
			_fcmd(cmd);
		else if (*(cmd->arg) != '\n')
		{
			cmd->status = 127;
			print_error(cmd, "not found\n");
		}
	}
}

/**
 * _fcmd - Forks an exec thread to run cmd.
 * @cmd: Pointer to the CMD structure.
 *
 * Return: void
 */
void _fcmd(CMD *cmd)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(cmd->path, cmd->argv, _get_environ(cmd)) == -1)
		{
			freecmd(cmd, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(cmd->status));
		if (WIFEXITED(cmd->status))
		{
			cmd->status = WEXITSTATUS(cmd->status);
			if (cmd->status == 126)
				print_error(cmd, "Permission denied\n");
		}
	}
}

