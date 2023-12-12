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
	int status;

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

		if (access(args[0], X_OK) == 0)
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
				waitpid(pid, &status, 0);
			}
		}
		else
		{
			fprintf(stderr, "%s: command not found\n", args[0]);
		}
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

	args[arg_count] = strtok(command, " ");
	while (args[arg_count] != NULL && arg_count < MAX_ARGS - 1)
	{
		arg_count++;
		args[arg_count] = strtok(NULL, " ");
	}
	args[arg_count] = NULL;
}
