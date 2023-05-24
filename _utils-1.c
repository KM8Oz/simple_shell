#include "main.h"

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

/**
 * _strrealloc - resize the memory block of a string
 * @ptr: pointer to the memory block to be resized
 * @size: new size for the memory block
 * Return: pointer to the resized memory block, or NULL on failure
 */
char *_strrealloc(char *ptr, size_t size)
{
	char *new_ptr;
	size_t i;
	size_t old_size;

	if (ptr == NULL)
	{
		new_ptr = malloc(size);
	}
	else
	{
		old_size = _strlen(ptr);
		new_ptr = malloc(size);
		if (new_ptr != NULL)
		{
			for (i = 0; i < old_size && i < size; i++)
			{
				new_ptr[i] = ptr[i];
			}
			free(ptr);
		}
	}

	return (new_ptr);
}

/**
 * _setenv - set an environment variable
 * @name: The name of the environment variable
 * @value: The value to set
 * @overwrite: Flag indicating whether to overwrite
 *  the variable if it already exists
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	size_t name_len = _strlen(name);
	size_t value_len = _strlen(value);
	char *existing_value = _getenv(name);
	int result;
	char *env_entry;

	if (name == NULL || value == NULL)
		return (-1);
	if (existing_value != NULL)
	{
		if (!overwrite)
			return (0);
		env_entry = _strdup(name);
		env_entry = _strrealloc(env_entry, name_len + 1 + value_len + 1);
		if (env_entry == NULL)
			return (-1);
		env_entry[name_len] = '=';
		_strcpy(env_entry + name_len + 1, value);
		result = putenv(env_entry);
		if (result != 0)
			return (-1);
		return (0);
	}
	env_entry = _strdup(name);
	env_entry = _strrealloc(env_entry, name_len + 1 + value_len + 1);
	if (env_entry == NULL)
		return (-1);
	env_entry[name_len] = '=';
	_strcpy(env_entry + name_len + 1, value);
	result = putenv(env_entry);
	if (result != 0)
		return (-1);

	return (0);
}

/**
 * getLastDirectory - Retrieve the last directory from
 *  a given path.
 * @path: A null-terminated string representing
 *  the path.
 *	Return: A pointer to the last directory in
 *  the path, or NULL if the path is empty or
 *  does not contain any directories.
 */

char *getLastDirectory(const char *path)
{
	char *lastDir;
	char *token;
	char *user = _getenv("USER");

	lastDir = NULL;
	token = strtok((char *)path, "/");

	while (token != NULL)
	{
		lastDir = token;
		token = strtok(NULL, "/");
	}
	if (_strncmp(user, lastDir, sizeof(lastDir)) == 0)
		return ("~");
	return (lastDir);
}
