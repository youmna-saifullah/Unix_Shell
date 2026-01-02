#include "shell.h"

int shell_rm(char **args) {
    // 1. Check if a filename/directory name was provided
    if (args[1] == NULL) {
        fprintf(stderr, "rm: missing operand\n");
        return 1;
    }

    int status;
    
    // 2. Logic to handle the -r flag for directories
    if (strcmp(args[1], "-r") == 0) {
        if (args[2] == NULL) {
            fprintf(stderr, "rm: missing operand after '-r'\n");
            return 1;
        }
        // rmdir only removes empty directories
        status = rmdir(args[2]);
    } else {
        // unlink removes files
        status = unlink(args[1]);
    }

    // 3. Error handling
    if (status == -1) {
        perror("rm");
    }

    // Return 1 to keep the shell loop running
    return 1;
}