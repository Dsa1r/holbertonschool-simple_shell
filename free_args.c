#include <stdlib.h>
#include "main.h"

void free_args(char **args)
{
	int i = 0;

	if (!args)
		return;

	while (args[i])
	{
		free(args[i]);
		i++;
	}

	free(args);
}
