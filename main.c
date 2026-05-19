#include "main.h"
#include <stdlib.h>  /* for atoi */

/**
 * main - Entry point for simple shell
 * @ac: argument count
 * @argv: argument vector
 * Return: 0 on success
 */
int main(int ac, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;
	int status = 0;
	int line_count = 0;
	int interactive = isatty(STDIN_FILENO);

	(void)ac;

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, "$ ", 2);
		nread = _getline(&line, &len);
		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(status);
		}
		line_count++;
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (line[0] == '\0')
			continue;
		args = tokenize(line);
		if (args == NULL || args[0] == NULL)
		{
			free_args(args);
			continue;
		}
		if (_strcmp(args[0], "exit") == 0)
		{
			int exit_status = status;
			if (args[1])
			{
				exit_status = atoi(args[1]);
			}

			free_args(args);
			free(line);
			exit(exit_status);
		}
		if (_strcmp(args[0], "env") == 0)
		{
			int i;

			for (i = 0; environ[i]; i++)
			{
				write(STDOUT_FILENO, environ[i], strlen(environ[i]));
				write(STDOUT_FILENO, "\n", 1);
			}
			free_args(args);
			continue;
		}
		status = execute_cmd(args, argv[0], line_count);
		free_args(args);
	}
	free(line);
	return (status);
}
