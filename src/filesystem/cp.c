#include "shell.h"

int shell_cp(char **args) {
    if (!args[1] || !args[2]) {
        fprintf(stderr, "Usage: cp SRC DEST\n");
        return 1;
    }

    int src = open(args[1], O_RDONLY);
    if (src < 0) { perror("cp"); return 1; }

    struct stat st;
    if (fstat(src, &st) < 0) {
        perror("cp");
        close(src);
        return 1;
    }

    int dst = open(args[2], O_WRONLY | O_CREAT | O_TRUNC, st.st_mode);
    if (dst < 0) { perror("cp"); close(src); return 1; }

    char buf[4096];
    ssize_t r;
    while ((r = read(src, buf, sizeof(buf))) > 0)
        write(dst, buf, r);

    close(src);
    close(dst);
    return 1;
}

