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
        strcpy(lines[line_count++], buffer);
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
        strcpy(filename, argv[1]);

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
        if (input[0] == 'q')
            break;
        if (input[0] == 's')
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
