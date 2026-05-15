#include "main.h"

/**
 * tokenize - Split a line into tokens (words)
 * @line: the input string
 * Return: array of strings (tokens)
 */
char **tokenize(char *line)
{
    char **args;
    char *token;
    int i = 0;

    args = malloc(sizeof(char *) * 64);
    if (!args)
        return (NULL);

    token = strtok(line, " \t\r\n");
    while (token != NULL && i < 63)
    {
        args[i++] = token;
        token = strtok(NULL, " \t\r\n");
    }
    args[i] = NULL;
    return (args);
}

/**
 * free_args - Free the args array
 * @args: array of strings
 */
void free_args(char **args)
{
    if (args)
        free(args);
}

/**
 * find_path - Search for cmd in PATH
 * @cmd: command name
 * Return: full path string or NULL
 */
char *find_path(char *cmd)
{
    char *path_env, *path_copy, *dir, *full_path;
    int i;

    /* If cmd already has a path */
    if (cmd[0] == '/' || cmd[0] == '.')
        return (cmd);

    for (i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
            break;
    }
    if (!environ[i])
        return (NULL);

    path_env = environ[i] + 5;
    path_copy = strdup(path_env);
    if (!path_copy)
        return (NULL);

    dir = strtok(path_copy, ":");
    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(cmd) + 2);
        if (!full_path)
        {
            free(path_copy);
            return (NULL);
        }
        sprintf(full_path, "%s/%s", dir, cmd);

        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return (full_path);
        }
        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}

/**
 * execute_cmd - Fork and execute a command
 * @args: argument array
 * @prog_name: name of shell (argv[0])
 * @line_count: current line number
 * Return: exit status
 */
int execute_cmd(char **args, char *prog_name, int line_count)
{
    pid_t pid;
    int status;
    char *cmd_path;

    cmd_path = find_path(args[0]);
    if (!cmd_path)
    {
        fprintf(stderr, "%s: %d: %s: not found\n",
                prog_name, line_count, args[0]);
        return (127);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        if (cmd_path != args[0])
            free(cmd_path);
        return (1);
    }

    if (pid == 0) /* Child process */
    {
        if (execve(cmd_path, args, environ) == -1)
        {
            fprintf(stderr, "%s: %d: %s: not found\n",
                    prog_name, line_count, args[0]);
            if (cmd_path != args[0])
                free(cmd_path);
            exit(127);
        }
    }

    /* Parent: wait for child */
    waitpid(pid, &status, 0);
    if (cmd_path != args[0])
        free(cmd_path);

    if (WIFEXITED(status))
        return (WEXITSTATUS(status));

    return (1);
}
