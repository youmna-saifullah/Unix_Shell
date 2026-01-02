#include "shell.h"
#include <signal.h>

int shell_kill(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "kill: usage: kill <pid> [sig]\n");
        return 1;
    }
    int pid = atoi(args[1]);
    int sig = (args[2] != NULL) ? atoi(args[2]) : SIGTERM;
    if (kill(pid, sig) == -1) {
        perror("kill");
    }
    return 1;
}
