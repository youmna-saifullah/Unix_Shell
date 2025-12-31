#include "shell.h"

int handle_redirection(char **args) {
    for (int i = 0; args[i]; i++) {
        if (strcmp(args[i], ">") == 0) {
            if (!args[i + 1]) {
                fprintf(stderr, "myshell: no output file\n");
                return -1;
            }

            int fd = open(args[i + 1],
                          O_WRONLY | O_CREAT | O_TRUNC,
                          0644);
            if (fd < 0) {
                perror("open");
                return -1;
            }

            dup2(fd, STDOUT_FILENO);
            close(fd);

            args[i] = NULL;   // terminate command
            return 1;
        }
    }
    return 0;
}

