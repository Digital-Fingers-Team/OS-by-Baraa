// Minimal console file manager

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void list_files(const char *path)
{
    DIR *dir = opendir(path);
    if (!dir)
    {
        printf("Cannot open directory %s\n", path);
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}

int main(int argc, char **argv)
{
    char path[256] = ".";
    if (argc > 1)
        strcpy(path, argv[1]);

    printf("BlackboxOS File Manager\n");
    printf("Listing files in %s:\n", path);
    list_files(path);

    return 0;
}
