#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

void process_command(char *command);

/**
 * main - a program that mimics the functons of a Unix shell
 * Return: 0 on success
 */

int main(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		printf("$ ");
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		command[strcspn(command, "\n")] = '\0';

		process_command(command);
	}
	return (0);
}

/**
 * process_command - a program that processes input commands from the user
 * @command: command from user
 * Return: non
 */
void process_command(char *command)
{
	char *args[MAX_ARGS];
	int arg_count = 0;
	char command_path[MAX_COMMAND_LENGTH];
	char **environment = environ;
	char *path = getenv("PATH");
	char *pathcopy = strdup(path);
	char *directory = strtok(pathcopy, ":");
	int found = 0;

	args[arg_count] = strtok(command, " ");

	while (args[arg_count] != NULL && arg_count < MAX_ARGS - 1)
	{
		arg_count++;
		args[arg_count] = strtok(NULL, " ");
	}
	args[arg_count] = NULL;

	if (strcmp(args[0], "exit") == 0)
	{
		printf("\n");
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		while (*environment != NULL)
		{
			printf("%s\n", *environment);
			environment++;
		}
		return;
	}

	while (directory != NULL)
	{
		snprintf(command_path, sizeof(command_path), "%s/%s", directory, args[0]);
		if (access(command_path, X_OK) == 0)
		{
			found = 1;
			break;
		}
		directory = strtok(NULL, ":");
	}
	free(pathcopy);
	if (found)
	{
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("Error forking");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			execve(args[0], args, NULL);
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
	}
	else
	{
		printf("%s: Command not found\n", args[0]);
	}
}
