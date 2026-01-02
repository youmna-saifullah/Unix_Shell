#include "shell.h"

int shell_clear(char **args) {
    (void)args; // Unused
    // ANSI escape codes: \033[H (move cursor to top), \033[J (clear screen)
    printf("\033[H\033[J");
    return 1;
}