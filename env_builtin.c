#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * _setenv - initialize or modify environment variable
 */
int _setenv(char **args)
{
	if (!args[1] || !args[2])
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (1);
	}

	if (setenv(args[1], args[2], 1) == -1)
	{
		perror("setenv");
		return (1);
	}

	return (0);
}

/**
 * _unsetenv - remove environment variable
 */
int _unsetenv(char **args)
{
	if (!args[1])
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (1);
	}

	if (unsetenv(args[1]) == -1)
	{
		perror("unsetenv");
		return (1);
	}

	return (0);
}
