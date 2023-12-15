#include "main.h"

/**
 * freecommands - a functions that frees up the memory used up...
 * by user commands
 * @commands: user command pointer
 * Return: non
 */
void freecommands(char ***command)
{
	size_t i;
	for (i = 0; (*command)[i] != NULL; i++)
	{
		free((*command)[i]);
		(*command)[i] = NULL;
	}
	free(*command);
	*command = NULL;
}
