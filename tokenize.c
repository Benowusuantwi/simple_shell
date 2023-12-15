#include "main.h"
/**
 * tokenize - a function that breaks users commands...
 * into tokens
 * @str: user command string
 * @delim: delimmitter
 * Return: character pointer
 */

char **tokenize(char *str, const char *delim)
{
	char **tokens = NULL, *token, *str_copy;
	size_t num_tokens = 0, i = 0;

	if (str == NULL || *str == '\0')
		return (NULL);

	str_copy = strdup(str);
	token = strtok(str_copy, delim);

	while (token != NULL)
	{
		++num_tokens;
		token = strtok(NULL, delim);
	}
	free(str_copy);

	if (num_tokens > 0)
	{
		tokens = malloc(sizeof(char *) * (num_tokens + 1));
		if (tokens == NULL)
			exit(EXIT_FAILURE);
		str_copy = strdup(str);
		token = strtok(str_copy, delim);

		while (token != NULL)
		{
			tokens[i++] = strdup(token);
			token = strtok(NULL, delim);
		}
		token[i] = NULL;
		free(str_copy);
	}
	return (tokens);
}
