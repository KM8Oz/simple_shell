#include "main.h"

/**
 * print_history - Displays the history list, one command per line,
 *                 preceded by line numbers starting at 0.
 * @cmd: Pointer to the CMD structure.
 *
 * Return: Always 0.
 */
int print_history(CMD *cmd)
{
	print_list(cmd->history);
	return (0);
}
