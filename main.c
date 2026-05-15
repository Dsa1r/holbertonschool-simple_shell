#include "main.h"

/**
 * main - Entry point for simple shell
 * Return: 0 on success
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char **args;
    int status = 0;
    int line_count = 0;
    int interactive = isatty(STDIN_FILENO);

    while (1)
    {
        if (interactive)
            write(STDOUT_FILENO, "$ ", 2);

        nread = getline(&line, &len, stdin);
        if (nread == -1)   /* EOF: Ctrl+D */
        {
            if (interactive)
                write(STDOUT_FILENO, "\n", 1);
            free(line);
            exit(status);
        }

        line_count++;

        /* Remove trailing newline */
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        /* Skip empty lines */
        if (line[0] == '\0')
            continue;

        args = tokenize(line);
        if (args == NULL || args[0] == NULL)
        {
            free_args(args);
            continue;
        }

        /* Handle built-in: exit */
        if (strcmp(args[0], "exit") == 0)
        {
            free_args(args);
            free(line);
            exit(status);
        }

        /* Handle built-in: env */
        if (strcmp(args[0], "env") == 0)
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

        status = execute_cmd(args, "hsh", line_count);
        free_args(args);
    }

    free(line);
    return (status);
}
