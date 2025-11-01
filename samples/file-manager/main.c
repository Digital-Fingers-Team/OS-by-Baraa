// Minimal console file manager (Corrected)

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h> // Required for errno

// Function to list files and directories in a given path
void list_files(const char *path)
{
    DIR *dir = opendir(path);
    if (!dir)
    {
        // Use perror to print a more descriptive error message
        perror("Cannot open directory");
        return;
    }

    struct dirent *entry;
    errno = 0; // Reset errno before calling readdir
    while ((entry = readdir(dir)) != NULL)
    {
        // Simple print of the entry name
        printf("%s\n", entry->d_name);
    }

    // Check if readdir failed due to an error
    if (errno != 0)
    {
        perror("Error reading directory");
    }

    closedir(dir);
}

int main(int argc, char **argv)
{
    char path[256] = "."; // Initialize with the default path

    // Check if a path is provided as a command-line argument
    if (argc > 1)
    {
        // Use snprintf for safe string copying to prevent buffer overflows.
        // It ensures the destination is null-terminated and won't write past its size.
        int written = snprintf(path, sizeof(path), "%s", argv[1]);
        
        // Check if the path was truncated
        if (written >= sizeof(path))
        {
            fprintf(stderr, "Error: Input path is too long and has been truncated.\n");
            return 1; // Exit with an error code
        }
    }

    printf("BlackboxOS File Manager\n");
    printf("Listing files in '%s':\n", path);
    printf("--------------------------\n");
    list_files(path);
    printf("--------------------------\n");

    return 0;
}
