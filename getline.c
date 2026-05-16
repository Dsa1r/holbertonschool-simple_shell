#include "main.h"

#define BUFFER_SIZE 1024

/**
 * _getline - custom getline without realloc
 * @lineptr: buffer
 * @n: size
 *
 * Return: number of chars read
 */
ssize_t _getline(char **lineptr, size_t *n)
{
	static char buffer[BUFFER_SIZE];
	static ssize_t index, bytes_read;
	ssize_t i = 0;

	if (*lineptr == NULL)
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


		if (i >= BUFFER_SIZE - 1)
			break;
	}

	(*lineptr)[i] = '\0';
	return (i);
}
