#include "main"

void executecommand(char *args[]);

/**
 * process_command - processes input from a user
 * @command: command from user
 * Return: Non
 *
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
