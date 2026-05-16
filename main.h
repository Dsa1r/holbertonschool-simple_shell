#include <sys/stat.h>
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/* Function prototypes */
char *find_path(char *cmd);
int execute_cmd(char **args, char *prog_name, int line_count);
char **tokenize(char *line);
void free_args(char **args);
ssize_t _getline(char **lineptr, size_t *n);
#endif /* MAIN_H */
