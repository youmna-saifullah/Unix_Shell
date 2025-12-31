#include "shell.h"

int shell_cat(char **args) {
    int fd_in = STDIN_FILENO;
    int fd_out = STDOUT_FILENO;
    char buf[4096];
    ssize_t r;

    if (args[1] && !args[2]) {
        fd_in = open(args[1], O_RDONLY);
        if (fd_in < 0)
            fd_in = open(args[1], O_CREAT | O_RDONLY, 0644);
    }

    while ((r = read(fd_in, buf, sizeof(buf))) > 0)
        write(fd_out, buf, r);

    if (fd_in != STDIN_FILENO) close(fd_in);
    return 1;
}

