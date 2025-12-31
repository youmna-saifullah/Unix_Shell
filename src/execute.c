#include "shell.h"
#include <sys/wait.h>

int execute_external(char **args) {
    pid_t pid = fork();

    if (pid == 0) {
        execvp(args[0], args);
        perror("myshell");
        exit(EXIT_FAILURE);
    }
    wait(NULL);
    return 1;
}

