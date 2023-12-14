#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

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
