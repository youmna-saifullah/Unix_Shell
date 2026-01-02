#include "shell.h"

int shell_chmod(char **args) {
    // 1. Validation: Ensure both permissions and filename are provided
    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "chmod: usage: chmod <octal_mode> <file>\n");
        return 1;
    }

    int perm = (int)strtol(args[1], NULL, 8);

    if (chmod(args[2], perm) == -1) {
        perror("chmod");
    }

    return 1;
}