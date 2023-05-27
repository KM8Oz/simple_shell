#include "main.h"

/**
 * get_old_file - Retrieves the history file path.
 * @cmd: Pointer to the CMD structure.
 *
 * Return: Allocated string containing the history file path.
 */
char *get_old_file(CMD *cmd)
{
	char *buf, *dir;

	dir = _getenv(cmd, "HOME=");
	if (!dir)
		return (NULL);

	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);

	buf[0] = '\0';
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);

	return (buf);
}

/**
 * write_history - Creates or appends to a history file.
 * @cmd: Pointer to the CMD structure.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(CMD *cmd)
{
	ssize_t fd;
	list_t *node;
	char *filename = get_old_file(cmd);

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	node = cmd->history;
	while (node)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
		node = node->next;
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Reads history from a file.
 * @cmd: Pointer to the CMD structure.
 *
 * Return: Number of history entries on success, 0 otherwise.
 */
int read_history(CMD *cmd)
{
	int linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_old_file(cmd);

	(void)linecount;
	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = '\0';
	close(fd);
	if (rdlen <= 0)
	{
		free(buf);
		return (0);
	}
	linecount = process_buffer(cmd, buf, fsize);
	free(buf);
	while (cmd->histcount >= HIST_MAX)
		delete_node_at_index(&(cmd->history), 0);
	renumber_history(cmd);
	return (cmd->histcount);
}

/**
 * process_buffer - count buff size
 * @cmd: Pointer to the CMD structure.
 * @buf: Buffer.
 * @size: line count.
 * Return: Always 0.
 */

int process_buffer(CMD *cmd, char *buf, ssize_t size)
{
	int i, last = 0, linecount = 0;

	for (i = 0; i < size; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			build_history_list(cmd, buf + last, linecount++);
			last = i + 1;
		}
	}
	if (last != i)
		build_history_list(cmd, buf + last, linecount++);
	cmd->histcount = linecount;

	return (linecount);
}

/**
 * build_history_list - Appends an entry to the history linked list.
 * @cmd: Pointer to the CMD structure.
 * @buf: Buffer.
 * @linecount: History line count.
 *
 * Return: Always 0.
 */
int build_history_list(CMD *cmd,

					   char *buf, int linecount)
{
	list_t *node = NULL;

	if (cmd->history)
		node = cmd->history;

	add_node_end(&node, buf, linecount);

	if (!cmd->history)
		cmd->history = node;
	return (0);
}
