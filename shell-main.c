#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024
char current_directory[BUFFER_SIZE];
/**
 * find_command_path - a function that takes a command as input,
 * searches for the command in the directories specified in the
 * PATH environment variable, and returns the full
 * path of the command if found
 * @buffer: ...
 * Return: void.
 */

char *find_command_path(char buffer[BUFFER_SIZE])
{
	char *path = getenv("PATH");
	char *copy_path = strdup(path);
	char *token;
	char *cmd = strtok(buffer, " ");
	char full_path[BUFFER_SIZE];

	if (strchr(buffer, '/') != NULL)
		return (cmd);
	token = strtok(copy_path, ":");
	while (token != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, cmd);
		if (access(full_path, X_OK) == 0)
		{
			return (strdup(full_path));
		}
		token = strtok(NULL, ":");
	}
	free(copy_path);
	return (cmd);
}

/**
 * get_last_directory_name - get last directory name
 * @path: ...
 * Return: void.
 */

char *get_last_directory_name(const char *path)
{
	char *token;
	char *lastDirName = NULL;

	char pathCopy[BUFFER_SIZE];
	strcpy(pathCopy, path);
	token = strtok(pathCopy, "/");

	while (token != NULL)
	{
		lastDirName = token;
		token = strtok(NULL, "/");
	}

	return (lastDirName);
}

/**
 * change_directory - change current directory.
 * @path: ...
 * Return: void.
 */

void change_directory(char *path)
{
	char *dir = path;
	char *HOME = getenv("HOME");
	size_t len;

	if (dir == NULL || *dir == '~')
		dir = HOME;
	len = strlen(dir);
	if (len > 0 && dir[len - 1] == '\n')
		dir[len - 1] = '\0';
	if (chdir(dir) != 0)
	{
		perror("chdir");
	}
	else
	{
		getcwd(current_directory, sizeof(current_directory));
	}
}

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
	char *cmds[64];

	if (pid == 0)
	{
		cmds[0] = strtok(buffer, " ");
		for (i = 1; i < 64; i++)
		{
			cmds[i] = strtok(NULL, " ");
			args[i] = cmds[i];
			if (cmds[i] == NULL)
				break;
		}
		if (strcmp(cmds[0], "cd") == 0)
		{
			change_directory(cmds[1]);
			exit(EXIT_SUCCESS);
		}
		cmds[0] = find_command_path(buffer);
		execve(cmds[0], cmds, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
		getcwd(current_directory, sizeof(current_directory));
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
		getcwd(current_directory, sizeof(current_directory));
		printf("%s($) ", get_last_directory_name(current_directory));
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
