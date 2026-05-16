#include "main.h"

#define BUFFER_SIZE 1024

/**
 * _getline - custom getline using read
 * @lineptr: pointer to buffer
 * @n: size of buffer
 *
 * Return: number of chars read
 */
ssize_t _getline(char **lineptr, size_t *n)
{
	static char buffer[BUFFER_SIZE];
	static ssize_t index, bytes_read;
	ssize_t i = 0;
	char *new_line;

	if (*lineptr == NULL || *n == 0)
	{
		*n = BUFFER_SIZE;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}

	while (1)
	{
		if (index >= bytes_read)
		{
			bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			index = 0;

			if (bytes_read <= 0)
				return (-1);
		}

		(*lineptr)[i++] = buffer[index++];

		if ((*lineptr)[i - 1] == '\n')
			break;

		/* expand buffer if needed */
		if (i >= (ssize_t)(*n - 1))
		{
			*n *= 2;
			new_line = realloc(*lineptr, *n);
			if (!new_line)
				return (-1);
			*lineptr = new_line;
		}
	}

	(*lineptr)[i] = '\0';
	return (i);
}
