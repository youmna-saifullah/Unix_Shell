#include "shell.h"

char *builtin_str[] = {"cd", "ls", "cat", "cp", "exit"};
int (*builtin_func[])(char **) = {
    shell_cd, shell_ls, shell_cat, shell_cp, shell_exit
};

#define BUILTIN_COUNT (sizeof(builtin_str) / sizeof(char *))

int shell_exit(char **args) {
    (void)args;
    printf("logout\n");
    exit(0);   
}


int execute_args(char **args) {
    if (!args[0]) return 1;

    // 1. Builtins
    for (int i = 0; i < BUILTIN_COUNT; i++) {
        if (strcmp(args[0], builtin_str[i]) == 0)
            return builtin_func[i](args);
    }

    // 2. Pipe
    if (handle_pipe(args))
        return 1;

    // 3. Redirection
    int saved_stdout = dup(STDOUT_FILENO);
    if (handle_redirection(args) == -1)
        return 1;

    // 4. External command
    execute_external(args);

    // restore stdout
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);

    return 1;
}

int main() {
    setup_signals();

    char *line;
    char **args;
    int status = 1;

    while (status) {
        if (sigsetjmp(ctrlc_buf, 1) != 0)
            printf("myshell> ");

        printf("myshell> ");
        line = read_line();
        args = split_line(line);
        status = execute_args(args);
        free(line);
        free(args);
    }
    return 0;
}

