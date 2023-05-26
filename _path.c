#include "shell.h"

/**
 * find_command_path - a function that takes a command as input,
 * searches for the command in the directories specified in the
 * PATH environment variable, and returns the full
 * path of the command if found
 * @buffer: ...
 * Return: void.
 */

char *find_command_path(char *buffer)
{
	char *path = _getenv0("PATH");
	const char *strings[3] = {NULL, "/", NULL};
	char *copy_path = _strdup(path);
	char *token;
	char *cmd = strtok(buffer, " ");
	char full_path[BUFFER_SIZE];

	if (_strchr(buffer, '/') != NULL)
		return (cmd);
	token = strtok(copy_path, ":");
	while (token != NULL)
	{
		strings[0] = token;
		strings[2] = cmd;
		_strcpy(full_path, join_strings(strings, 3));
		if (access(full_path, X_OK) == 0)
			return (_strdup(full_path));
		token = strtok(NULL, ":");
	}
	free(copy_path);
	return (cmd);
}

/**
 * join_strings - join a list of string based on order.
 * @strings: array of strings to join.
 * @count: strings count.
 *
 * Return: Pointer to string representing joined strings.
 */

char *join_strings(const char **strings, int count)
{
	int total_length = 0, i, position;
	char *joined_string;

	for (i = 0; i < count; i++)
	{
		total_length += _strlen(strings[i]);
	}
	joined_string = (char *)malloc((total_length + 1) * sizeof(char));
	if (joined_string == NULL)
	{
		_putstr("Failed to allocate memory.\n");
		return (NULL);
	}
	position = 0;
	for (i = 0; i < count; i++)
	{
		_strcpy(joined_string + position, strings[i]);
		position += _strlen(strings[i]);
	}
	joined_string[total_length] = '\0';

	return (joined_string);
}

/**
 * _strcpy - copy the string pointed by src to dest
 * @dest: destination string
 * @src: source string
 * Return: pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	char *dest_start = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';

	return (dest_start);
}
