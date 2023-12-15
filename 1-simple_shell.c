#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

void executecommand(char **args, char *argv0, size_t arg_count);

/**
 * main - a program that mimics the functons of a Unix shell
 * @argc: arguments used
 * @argv: argument vector
 * Return: 0 on success
 */

int main(__attribute__((unused)) int argc, char *argv[])
{
	char *command_line = NULL, **commands = NULL;
	size_t command_length = 0, arg_count = 0;
	ssize_t line_read;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		fflush(stdout);
		line_read = getline(&command_line, &command_length, stdin);
		++arg_count;

		if (line_read == -1)
		{
			free(command_line);
			command_line = NULL;
			if (isatty(STDIN_FILENO))
				printf("\n");
			exit(0);
		}
		command_line[line_read - 1] = '\0';
		if (*command_line == '\0')
		{
			free(command_line);
			command_line = NULL;
			continue;
		}
		commands = tokenize(command_line, " ");
		if (commands == NULL)
		{
			free(command_line);
			command_line = NULL;
			continue;
		}
		executecommand(commands, argv[0], arg_count);
		freecommands(&commands);
		free(command_line);
		command_line = NULL;
	}
	return (0);
}

/**
 * executecommand - a function that executes input commands...
 * from the user
 * @args: input arguments from the user
 * @argv0: argument vector
 * @arg_count: argument counter
 * Return: non
 */
void executecommand(char **args, char *argv0, size_t arg_count)
{
	pid_t pid = fork();
	int status;

	if (access(args[0], X_OK) == -1)
	{
		get_path(&args[0]);
		if (args != NULL && access(args[0], X_OK) == -1)
		{
			fprintf(stderr, "%s: %lu :%s: not found\n", argv0, arg_count, args[0]);
			freecommands(args);
			return;
		}
	}

	if (pid == -1)
	{
		perror("Error forking");
		freecommands(args);
		exit(EXIT_FAILURE);
		return;
	}
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
			perror("execve");
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	freecommands(args);
}
