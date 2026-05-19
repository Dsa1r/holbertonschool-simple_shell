#include "main.h"
#include <signal.h>
#include <unistd.h>

/**
 * handle_sigint - handle Ctrl+C
 * @sig: signal number
 */
void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}
