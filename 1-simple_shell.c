#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include "main.h"

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
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			else
			{
				perror("Error reading command");
				exit(EXIT_FAILURE);
			}
		}

		command[strcspn(command, "\n")] = '\0';

		if (*command == '\0')
		{
			continue;
		}

		process_command(command);
	}
	return (0);
}

void executecommand(char *args[]);
/**
 * process_command - a function that processes commands typed...
 * by the user
 * @command: input
 * Return: non
 */

void process_command(char *command)
{
	char *args[MAX_ARGS], **environment = environ;
	int arg_count = 0;

	args[arg_count] = strtok(command, "");
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
	executecommand(args);
}
/**
 * executecommand - a function that executes input commands...
 * from the user
 * @args: input arguments from the user
 * Return: non
 */
void executecommand(char *args[])
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Error forking");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execvp(args[0], args);
		perror(args[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}
