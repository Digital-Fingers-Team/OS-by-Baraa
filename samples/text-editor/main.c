// Minimal console text editor (fallback for Windows environment)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LINE_LEN 256

char lines[MAX_LINES][MAX_LINE_LEN];
int line_count = 0;

void load_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
        return;
    char buffer[MAX_LINE_LEN];
    while (fgets(buffer, sizeof(buffer), file) && line_count < MAX_LINES)
    {
        // Ensure null termination and bounds checking
        buffer[MAX_LINE_LEN - 1] = '\0';
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0'; // Remove newline
        }
        if (len < MAX_LINE_LEN)
        {
            strcpy(lines[line_count++], buffer);
        }
    }
    fclose(file);
}

void save_file(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
        return;
    for (int i = 0; i < line_count; i++)
    {
        fputs(lines[i], file);
    }
    fclose(file);
}

int main(int argc, char **argv)
{
    char filename[256] = "untitled.txt";
    if (argc > 1)
    {
        if (strlen(argv[1]) < sizeof(filename))
        {
            strcpy(filename, argv[1]);
        }
        else
        {
            printf("Filename too long\n");
            return 1;
        }
    }

    load_file(filename);

    printf("BlackboxOS Text Editor\n");
    printf("Commands: 'q' to quit, 's' to save\n");
    printf("Enter text (one line at a time):\n");

    char input[MAX_LINE_LEN];
    while (1)
    {
        printf("> ");
        if (!fgets(input, sizeof(input), stdin))
            break;
        // Ensure null termination
        input[MAX_LINE_LEN - 1] = '\0';
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
        {
            input[len - 1] = '\0';
        }
        if (strcmp(input, "q") == 0)
            break;
        if (strcmp(input, "s") == 0)
        {
            save_file(filename);
            printf("Saved to %s\n", filename);
            continue;
        }
        if (line_count < MAX_LINES)
        {
            strcpy(lines[line_count++], input);
        }
    }

    return 0;
}
