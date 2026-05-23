#include "main.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

/**
 * _setenv - create or modify an environment variable
 * @args: arguments array
 * Return: 0 on success, 1 on failure
 */
int _setenv(char **args)
{
	int i, j;
	char *new_var;
	char **new_env;
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
			environ[i] = new_var;
			return (0);
		}
	}

	i = 0;
	while (environ[i])
		i++;

	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(new_var);
		return (1);
	}

	for (j = 0; j < i; j++)
		new_env[j] = environ[j];

	new_env[i] = new_var;
	new_env[i + 1] = NULL;

	environ = new_env;

	return (0);
}

/**
 * _unsetenv - remove an environment variable
 * @args: arguments array
 * Return: 0 on success, 1 on failure
 */
int _unsetenv(char **args)
{
	int i, j, len;
	char **new_env;

	if (!args[1])
	{
		write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", 25);
		return (1);
	}

	len = strlen(args[1]);

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], args[1], len) == 0 &&
		    environ[i][len] == '=')
		{
			for (j = i; environ[j]; j++)
				environ[j] = environ[j + 1];
			break;
		}
	}

	i = 0;
	while (environ[i])
		i++;

	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (1);

	for (j = 0; j < i; j++)
		new_env[j] = environ[j];

	new_env[i] = NULL;

	environ = new_env;

	return (0);
}
