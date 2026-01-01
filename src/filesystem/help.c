#include <stdio.h>
#include <string.h>

typedef struct {
    char cmd[20];
    char info[200];
} HelpEntry;

HelpEntry help_db[] = {
    {"ls", "ls - list directory contents"},
    {"cd", "cd - change directory"},
    {"exit", "exit - exit the shell"},
    {"history", "history - show command history"},
    {"export", "export VAR=value - set environment variable"},
    {"man", "man command - show manual"},
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: help <command>\n");
        return 1;
    }

    for (int i = 0; i < sizeof(help_db)/sizeof(help_db[0]); i++) {
        if (strcmp(argv[1], help_db[i].cmd) == 0) {
            printf("%s\n", help_db[i].info);
            return 0;
        }
    }

    printf("help: no help found for '%s'\n", argv[1]);
    return 1;
}
