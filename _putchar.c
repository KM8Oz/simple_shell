#include "main.h"

/**
 * _putchar - print char in stdout
 * @c: one char
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _putstr - print str in stdout
 * @c: char*
 *
 * Return: ...
 */

int _putstr(char *c)
{
	int i = 0;

	while (*(c + i))
	{
		_putchar(*(c + i));
		i++;
	}

	return (sizeof(char) * _strlen(c));
}

