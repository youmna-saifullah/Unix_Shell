#include "shell.h"

int shell_echo(char **args) {
    for (int i = 1; args[i] != NULL; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
    return 1; // Return type int hona chahye
}
