#include "main.h"


/**
 * find_path - Search for cmd in PATH
 * @cmd: command name
 * Return: full path string or NULL
 */
char *find_path(char *cmd)
{
	char *path_copy, *dir, *full_path;
	int i;
	struct stat st;

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			break;
	}
	if (!environ[i] || strlen(environ[i]) == 5)
		return (NULL);

	path_copy = strdup(environ[i] + 5);
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
		if (stat(full_path, &st) == 0)
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

	if (pid == 0)
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

	waitpid(pid, &status, 0);
	if (cmd_path != args[0])
		free(cmd_path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
