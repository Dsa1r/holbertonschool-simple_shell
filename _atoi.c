#include "main.h"

/**
 * _atoi - convert string to integer
 * @str: input string
 * Return: integer value
 */
int _atoi(char *str)
{
	int i = 0;
	int num = 0;
	int sign = 1;

	if (!str)
		return (0);

	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}

	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		num = num * 10 + (str[i] - '0');
		i++;
	}

	return (num * sign);
}
