#include "main.h"

/**
 * clear_screen - constract comand from buffer and execute it,
 * Return: void.
 */

int clear_screen(void)
{
	_putstr("\033[2J\033[H");
	return (0);
}

/**
 * switch_builtin_command - Execute actions based on input command.
 *
 * This function takes an input command as a string and uses a switch
 * statement to determine the appropriate action based on the command.
 * It compares the command with different built-in commands and executes
 * the corresponding code block for the matching command.
 *
 * @cmds: The input command and args to switch.
 * Return: int.
 */
int switch_builtin_command(char *cmds[64])
{
	if (_strncmp(cmds[0], "cd", 3UL) == 0)
		return (change_directory(cmds[1]));
	if (_strncmp(cmds[0], "clear", 6UL) == 0)
		return (clear_screen());
	if (_strncmp(cmds[0], "exit", 6UL) == 0 || _strncmp(cmds[0], "^C", 3UL) == 0)
		exit(0);
	return (-1);
}
