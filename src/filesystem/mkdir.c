#include "shell.h"

int shell_mkdir(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "mkdir: missing operand\n");
        return 1; 
    }

    if (mkdir(args[1], 0755) == -1) {
        perror("mkdir");
    }

    return 1; 
}