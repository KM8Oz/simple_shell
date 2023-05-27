#include "main.h"

/**
 * if_exist - checks if a file exists and is executable
 * @cmd: the CMD struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int if_exist(CMD *cmd, char *path)
{
	struct stat st;

	(void)cmd;
	if (!path || stat(path, &st) != 0)
		return (0);

	if (st.st_mode & S_IFREG)
		return (1);

	return (0);
}

/**
 * _dupstr - duplicates characters from a string
 * @source: the source string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to the new buffer
 */
char *_dupstr(const char *source, int start, int stop)
{
	static char buffer[1024];
	int i, k = 0;

	for (i = start; i < stop; i++)
	{
		if (source[i] != ':')
			buffer[k++] = source[i];
	}

	buffer[k] = '\0';
	return (buffer);
}


/**
 * renumber_history - Renumbers the history linked list after modifications.
 * @cmd: Pointer to the CMD structure.
 *
 * Return: The new histcount.
 */
int renumber_history(CMD *cmd)
{
	list_t *node = cmd->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (cmd->histcount = i);
}
