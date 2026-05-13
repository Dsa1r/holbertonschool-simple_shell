#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - Entry point of the simple shell
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}

		if (read > 1)
			write(STDOUT_FILENO, line, read);
	}

	free(line);
	return (0);
}
