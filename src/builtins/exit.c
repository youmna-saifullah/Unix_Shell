#include "shell.h"
#include <stdlib.h>

int shell_exit(char **args)
{
    int status = 0;
    if (args[1])
        status = atoi(args[1]);
    exit(status);
}

