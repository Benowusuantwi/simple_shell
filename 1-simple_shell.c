#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

void executecommand(char *args, char *argv[]);

/**
 * handle_user_command - a program that reads user commands
 * @command_line: pointer to user command
 * @cmd_len: pointer to the length of the input command
 */

void handle_user_command(char **command_line, size_t *cmd_len)
{
	size_t cmd_count = 0;
	ssize_t line_read;

	if (isatty(STDIN_FILENO))
		_printf("$ ");
	fflush(stdout);
	line_read = getline(command_line, cmd_len, stdin);
	++cmd_count;

	if (line_read == -1)
	{
		free(*command_line);
		*command_line = NULL;
		if (isatty(STDIN_FILENO))
			_printf("\n");
		exit(EXIT_SUCCESS);
	}
	(*command_line)[line_read - 1] = '\0';
}
/**
 * _processcommand - processes a command from the user
 * @command_line: pointer to the user command
 */
void _processcommand(char *command_line)
{
	char **commands = tokenize(command_line, " ");

	if (commands != NULL && commands[0] != NULL)
	{
		if (strcmp(commands[0], "exit") == 0)
		{
			freecommands(commands);
			free(command_line);
			exit(0);
		}
		else
		{
			executecommand(command_line, commands);
		}
		freecommands(commands);
	}
	else
	{
		_printf("Invalid input.\n");
	}
}

/**
 * main - accessing simple shell
 * @argc: Number of command line arguments
 * @argv: argument vector
 *
 * Return: 0 on Success
 */
int main(int argc, char *argv[])
{
	char *command_line = NULL, **commands = NULL;
	size_t i = 0, cmd_count = 0;
	ssize_t line_read;

	(void)argc, (void)argv;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$");
		fflush(stdout);
		line_read = getline(&command_line, &i, stdin);
		++cmd_count;

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
			continue;

		commands = tokenize(command_line, " ");
		if (commands == NULL)
			continue;

		executecommand(command_line, commands);
		freecommands(commands);
		free(command_line);
		commands = NULL;
		command_line = NULL;
	}
	return (0);
}

/**
 * executecommand - a function that executes input commands...
 * from the user
iii * @args: input arguments from the user
 * @argv: argument vector
 * Return: non
 */
void executecommand(char *args, char *argv[])
{
	pid_t child_p;
	int status;

	if (access(args, X_OK | R_OK) == -1)
	{
		/*get_path(&args);*/
		if (args != NULL && access(args, X_OK) == -1)
		{
			fprintf(stderr, "%s: %s: not found\n", argv[0], args);
			return;
		}
	}
	child_p = fork();

	if (child_p == -1)
	{
		perror("Error forking");
		exit(EXIT_FAILURE);
		return;
	}
	if (child_p == 0)
	{
		if (execve(args, argv, environ) == -1)
			perror("execve");
	}
	else
	{
		waitpid(child_p, &status, 0);
	}
	/*freecommands(args);*/
}
