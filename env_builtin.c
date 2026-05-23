#include "main.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * _setenv - initialize or modify an environment variable
 * @args: arguments array
 * Return: 0 on success, 1 on failure
 */
int _setenv(char **args)
{
	int i;
	char *new_var;
	size_t len;

	if (!args[1] || !args[2])
	{
		write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 29);
		return (1);
	}

	len = strlen(args[1]) + strlen(args[2]) + 2;
	new_var = malloc(len);
	if (!new_var)
		return (1);

	strcpy(new_var, args[1]);
	strcat(new_var, "=");
	strcat(new_var, args[2]);

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], args[1], strlen(args[1])) == 0 &&
		    environ[i][strlen(args[1])] == '=')
		{
			/* DO NOT FREE environ[i] */
			environ[i] = new_var;
			return (0);
		}
	}

	free(new_var);
	return (0);
}

/**
 * _unsetenv - remove an environment variable
 * @args: arguments array
 * Return: 0 on success, 1 on failure
 */
int _unsetenv(char **args)
{
	int i, j;

	if (!args[1])
	{
		write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", 25);
		return (1);
	}

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], args[1], strlen(args[1])) == 0 &&
		    environ[i][strlen(args[1])] == '=')
		{
			/* DO NOT FREE */
			for (j = i; environ[j]; j++)
				environ[j] = environ[j + 1];

			return (0);
		}
	}

	return (0);
}
