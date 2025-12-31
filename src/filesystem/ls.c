#include "shell.h"

static void print_permissions(mode_t mode) {
    printf(S_ISDIR(mode) ? "d" :
           S_ISLNK(mode) ? "l" : "-");

    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");

    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");

    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

static void print_details(const char *path, const char *file) {
    struct stat st;
    char fullpath[1024];

    snprintf(fullpath, sizeof(fullpath), "%s/%s", path, file);

    // lstat => symlinks bhi correctly handle
    if (lstat(fullpath, &st) == -1)
        return;

    print_permissions(st.st_mode);

    struct passwd *pw = getpwuid(st.st_uid);
    struct group  *gr = getgrgid(st.st_gid);

    char timebuf[64];
    struct tm *tm = localtime(&st.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm);

    printf(" %3lu %-8s %-8s %8ld %s %s",
           st.st_nlink,
           pw ? pw->pw_name : "unknown",
           gr ? gr->gr_name : "unknown",
           st.st_size,
           timebuf,
           file);

    // show symlink target
    if (S_ISLNK(st.st_mode)) {
        char linkbuf[1024];
        ssize_t len = readlink(fullpath, linkbuf, sizeof(linkbuf)-1);
        if (len > 0) {
            linkbuf[len] = '\0';
            printf(" -> %s", linkbuf);
        }
    }

    printf("\n");
}

int shell_ls(char **args) {
    char *target = ".";
    int long_format = 0;

    if (args[1]) {
        if (strcmp(args[1], "-l") == 0) {
            long_format = 1;
            if (args[2])
                target = args[2];
        } else {
            target = args[1];
        }
    }

    DIR *dir = opendir(target);
    if (!dir) {
        perror("ls");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.')
            continue;

        if (long_format)
            print_details(target, entry->d_name);
        else
            printf("%s  ", entry->d_name);
    }

    if (!long_format)
        printf("\n");

    closedir(dir);
    return 1;
}

