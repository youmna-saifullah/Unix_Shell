#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int shell_export(char **args)
{
    if (!args[1]) {
        fprintf(stderr, "export: usage: export VAR=value\n");
        return 1;
    }

    for (int i = 1; args[i]; i++) {
        char *eq = strchr(args[i], '=');

        if (!eq) {
            fprintf(stderr, "export: invalid format: %s\n", args[i]);
            continue;
        }

        *eq = '\0';
        setenv(args[i], eq + 1, 1);
    }

    return 1;   // keep shell running
}
