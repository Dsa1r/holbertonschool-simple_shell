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


ssize_t _getline(char **lineptr, size_t *n);
int _strcmp(const char *s1, const char *s2);
char **tokenize(char *line);
void free_args(char **args);
int _atoi(char *str);
#endif /* MAIN_H */
