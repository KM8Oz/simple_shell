#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

/**
 * run - constract comand from buffer and execute it,
 * @pid: ...
 * @buffer: ...
 * Return: void.
 */

void run(pid_t pid, char buffer[BUFFER_SIZE])
{
	int i, status;
	char *args[64];

	if (pid == 0)
	{
		args[0] = strtok(buffer, " ");
		for (i = 1; i < 64; i++)
		{
			args[i] = strtok(NULL, " ");
			if (args[i] == NULL)
				break;
		}
		execve(args[0], args, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
}

/**
 * main - simple shell
 * Return: int.
 */

int main(void)
{
	char buffer[BUFFER_SIZE];
	size_t len;
	pid_t pid;

	while (1)
	{
		printf("($) ");
		fflush(stdout);
		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
			break;
		len = strlen(buffer);
		if (len > 0 && buffer[len - 1] == '\n')
			buffer[len - 1] = '\0';
		if (strcmp(buffer, "exit") == 0)
			break;
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else
		{
			run(pid, buffer);
		}
	}

	return (EXIT_SUCCESS);
}
