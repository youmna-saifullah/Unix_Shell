#include "shell.h"

int shell_pwd(char **args) {
    // Avoid "unused parameter" warnings
    (void)args; 

    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd");
    }

    return 1;
}