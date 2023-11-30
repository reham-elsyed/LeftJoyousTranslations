#ifndef __MAIN_H
#define __MAIN_H
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#define MAX_BUFSIZE 1024
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"
extern char **environ;
void mask(void);
char *readprompt(void);
char **parseline(char *line);
int _cd(char **args);
int _help(char **args);
int r_exit(char **args);
char *_getenv(const char *name);
char *locate(const char *filename);
char *join_path(const char sep,const char *path1,const char *path2);
char *_strdup(const char *str);

#endif