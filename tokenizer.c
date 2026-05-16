#include "main.h"

/**
 * tokenize - split input into arguments
 * @line: input string
 *
 * Return: array of strings
 */
char **tokenize(char *line)
{
	char **args;
	int i = 0;
	int j = 0;
	int k = 0;

	args = malloc(sizeof(char *) * 64);
	if (!args)
		return (NULL);

	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;

		if (line[i] == '\0')
			break;

		args[j] = malloc(128);
		if (!args[j])
			return (NULL);

		k = 0;

		while (line[i] && line[i] != ' ' &&
		       line[i] != '\t' && line[i] != '\n')
		{
			args[j][k++] = line[i++];
		}

		args[j][k] = '\0';
		j++;
	}

	args[j] = NULL;
	return (args);
}
