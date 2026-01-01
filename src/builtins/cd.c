#include "shell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static char prev_dir[PATH_MAX] = "";

int shell_cd(char **args)
{
    char cwd[PATH_MAX];
    char *path;

    getcwd(cwd, sizeof(cwd));

    if (!args[1]) {
        path = getenv("HOME");
        if (!path) {
            fprintf(stderr, "cd: HOME not set\n");
            return 1;
        }
    }
    else if (strcmp(args[1], "-") == 0) {
        if (strlen(prev_dir) == 0) {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return 1;
        }
        path = prev_dir;
        printf("%s\n", path);
    }
    else {
        path = args[1];
    }

    if (chdir(path) != 0) {
        perror("cd");
        return 1;
    }

    strcpy(prev_dir, cwd);
    setenv("OLDPWD", cwd, 1);
    setenv("PWD", path, 1);

    return 1;
}

