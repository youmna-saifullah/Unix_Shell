#include "shell.h"

char *read_line() {
    char *line = NULL;
    size_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1) {
        if (feof(stdin)) exit(EXIT_SUCCESS);
        perror("readline");
        exit(EXIT_FAILURE);
    }
    return line;
}

char **split_line(char *line) {
    int bufsize = TOKEN_BUFSIZE, pos = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    if (!tokens) exit(EXIT_FAILURE);

    char *token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL) {
        tokens[pos++] = token;

        if (pos >= bufsize) {
            bufsize *= 2;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) exit(EXIT_FAILURE);
        }
        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[pos] = NULL;
    return tokens;
}

