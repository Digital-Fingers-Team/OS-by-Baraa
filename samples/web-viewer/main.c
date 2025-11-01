// Minimal console web viewer (stub, requires libcurl)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: web-viewer <url>\n");
        return 1;
    }

    // Basic URL validation (simple check for http/https)
    if (strlen(argv[1]) < 7 || (strncmp(argv[1], "http://", 7) != 0 && strncmp(argv[1], "https://", 8) != 0))
    {
        printf("Invalid URL: must start with http:// or https://\n");
        return 1;
    }

    printf("BlackboxOS Web Viewer\n");
    printf("Viewing %s (stub implementation)\n", argv[1]);
    // In full impl, use libcurl to fetch and display HTML

    return 0;
}
