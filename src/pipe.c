#include "shell.h"
#include <sys/wait.h>

int handle_pipe(char **args) {
    int i;
    for (i = 0; args[i]; i++) {
        if (strcmp(args[i], "|") == 0)
            break;
    }

    if (!args[i]) return 0;   // no pipe

    args[i] = NULL;
    char **cmd1 = args;
    char **cmd2 = &args[i + 1];

    int fd[2];
    pipe(fd);

    if (fork() == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        execvp(cmd1[0], cmd1);
        perror("exec");
        exit(1);
    }

    if (fork() == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        execvp(cmd2[0], cmd2);
        perror("exec");
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 1;
}

