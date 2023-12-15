#include "main.h"
/**
 * get_path - a fuction ...
 * @command: user command
 * Return: non
 */

void get_path(char **command)
{
	char *path_dir = getenv("PATH");
	char *path_env = strdup(path_dir);
	char *dir = strtok(path_env, ":");
	char *full_path = NULL;

	if (path_dir == NULL)
		return;
	while (dir != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(*command) + 2);
		if (full_path == NULL)
		{
			fprintf(stderr, "Memory allocation failed\n");
			return;
		}
		sprintf(full_path, "%s/%s", dir, *command);
		if (access(full_path, X_OK) == 0)
		{
			free(*command);
			*command = strdup(full_path);
			free(full_path);
			break;
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_env);
}
