#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <signal.h>
#include <setjmp.h>

#define LSH_TOK_DELIM " \t\r\n\a"
#define TOKEN_BUFSIZE 64

extern sigjmp_buf ctrlc_buf;

int execute_external(char **args);
int handle_redirection(char **args);
int handle_pipe(char **args);

/* Core */
void setup_signals();
char *read_line();
char **split_line(char *line);
int execute_args(char **args);

/* Builtins */
int shell_cd(char **args);
int shell_ls(char **args);
int shell_cat(char **args);
int shell_cp(char **args);
int shell_exit(char **args);
int shell_history(char **args);
int shell_export(char **args);


/* Future Commands */
int shell_help(char **args);
int shell_history(char **args);
int shell_pwd(char **args);
int shell_echo(char **args);
int shell_export(char **args);
int shell_kill(char **args);
int shell_grep(char **args);
int shell_mkdir(char **args);
int shell_rm(char **args);
int shell_mv(char **args);
int shell_chmod(char **args);
int shell_man(char **args);
int shell_clear(char **args);

#endif

