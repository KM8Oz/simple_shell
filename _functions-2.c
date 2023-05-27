#include "main.h"

/**
 * is_cmd - determines if a file is an executable command
 * @cmd: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(CMD *cmd, char *path)
{
	struct stat st;

	(void)cmd;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
