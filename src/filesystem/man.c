#include <stdio.h>
#include <string.h>

typedef struct {
    char cmd[20];
    char manual[500];
} ManPage;

ManPage man_db[] = {
    {"ls", 
     "NAME\n"
     "    ls\n\n"
     "DESCRIPTION\n"
     "    Lists information about files and directories.\n"},

    {"cd",
     "NAME\n"
     "    cd\n\n"
     "DESCRIPTION\n"
     "    Changes the current working directory.\n"},

    {"exit",
     "NAME\n"
     "    exit\n\n"
     "DESCRIPTION\n"
     "    Terminates the shell session.\n"},

    {"history",
     "NAME\n"
     "    history\n\n"
     "DESCRIPTION\n"
     "    Displays previously entered commands.\n"}
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: man <command>\n");
        return 1;
    }

    for (int i = 0; i < sizeof(man_db)/sizeof(man_db[0]); i++) {
        if (strcmp(argv[1], man_db[i].cmd) == 0) {
            printf("%s", man_db[i].manual);
            return 0;
        }
    }

    printf("No manual entry for %s\n", argv[1]);
    return 1;
}
