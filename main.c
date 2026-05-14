#include "main.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    pid_t pid;
    int status;

    while (1)
    {
        write(STDOUT_FILENO, "#cisfun$ ", 10);

        if (getline(&line, &len, stdin) == -1)
        {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }

        line[strcspn(line, "\n")] = '\0';

        pid = fork();

        if (pid == 0)
        {
            char *argv[] = {line, NULL};

            execve(line, argv, environ);

            perror("./shell");
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(&status);
        }
    }

    free(line);
    return (0);
}
