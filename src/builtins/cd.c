#include "shell.h"

int shell_cd(char **args) {
    if (!args[1]) {
        char *home = getenv("HOME");
        if (!home || chdir(home) != 0)
            perror("cd");
    } else {
        if (chdir(args[1]) != 0)
            perror("cd");
    }
    return 1;
}

