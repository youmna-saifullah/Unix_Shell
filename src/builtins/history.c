#include "shell.h"
#include <stdio.h>

#define HISTORY_FILE ".myshell_history"

int shell_history(char **args)
{
    (void)args;

    FILE *fp = fopen(HISTORY_FILE, "r");
    if (!fp) {
        perror("history");
        return 1;
    }

    char line[1024];
    int count = 1;

    while (fgets(line, sizeof(line), fp)) {
        printf("%4d  %s", count++, line);
    }

    fclose(fp);
    return 1;
}
