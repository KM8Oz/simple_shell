#include "main.h"

/**
 * main - main function
 * @argc: arguments count
 * @argv: arguments vector
 * Return: 0 or 1 depent on exit status
 */
int main(int argc, char **argv)
{
	CMD cmd[] = {CMD_STAR};
	int file_id = 2;

	if (check_if_file_exist(&file_id, cmd, argc, argv) == -1)
		return (EXIT_FAILURE);
	_add_env_list(cmd);
	read_history(cmd);
	loop(cmd, argv);
	return (EXIT_SUCCESS);
}
