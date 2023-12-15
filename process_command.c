#include "main.h"
/**
 * execute_command - a function that executes user commands
 * @args: input arguments from the user
 * Return: non
 */

void execute_command(char *args[])
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

/**
 * processcommand - processes input from a user
 * @command: command from user
 * Return: Non
 *
 */

void processcommand(char *command)
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

	execute_command(args);
}
