#include "shell.h"

/**
 * print_environment - function that prints the environment
 * variables.
 * @args: args vectors
 * Return: void.
 */

int print_environment(char **args)
{
	char **env = environ;

	(void)args;
	while (*env != NULL)
	{
		_putstr(*env);
		_putstr("\n");
		env++;
	}
	return (0);
}

/**
 * _getenv - Retrieves the value of an environment variable.
 * @key: The key of the environment variable to be retrieved.
 *
 * Return: Pointer to a string representing the value of
 * the environment variable and key and index.
 */

ENV *_getenv(char *key)
{
	int i = 0;
	char *tempkey;
	char *tempvalue;
	ENV *tupele = NULL;

	while (*(environ + i))
	{
		tempkey = strtok(*(environ + i), "=");
		tempvalue = strtok(NULL, "=");
		if (_strncmp(tempkey, key, 4UL) == 0)
		{
			tupele->index = i;
			tupele->key = tempkey;
			tupele->value = tempvalue;
			return (tupele);
		}
		i++;
	}
	return (tupele);
}

/**
 * _getenv0 - _getenv clone
 * @name: char's pointers
 * Return:...
 */

char *_getenv0(const char *name)
{
	char **env;
	size_t nameLength;

	if (name == NULL || *name == '\0')
		return (NULL);
	nameLength = _strlen(name);

	for (env = environ; *env != NULL; env++)
		if (_strncmp(*env, name, nameLength) == 0 && (*env)[nameLength] == '=')
			return (&((*env)[nameLength + 1]));

	return (NULL);
}

/**
 * clear_screen - constract comand from buffer and execute it,
 * @args: args vectors
 * Return: void.
 */

int clear_screen(char **args)
{
	(void)args;
	_putstr("\033[2J\033[H");
	return (0);
}

/**
 * _realloc - realloc clone function using malloc.
 * @ptr: void vector
 * @size: vector size
 * Return: void.
 */

void *_realloc(void *ptr, size_t size)
{
	size_t old_size, i;
	void *new_ptr;
	char *src;
	char *dest;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	old_size = sizeof(ptr);
	if (size <= old_size)
		return (ptr);
	new_ptr = malloc(size);
	if (new_ptr == NULL)
	{
		return (NULL);
		src = (char *)ptr;
		dest = (char *)new_ptr;
		for (i = 0; i < old_size; i++)
			dest[i] = src[i];
		free(ptr);

		return (new_ptr);
	}
	return (new_ptr);
}

