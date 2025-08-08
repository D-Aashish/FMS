#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *source, *dest;
    char *buffer;
    size_t bytes;
    size_t bufsize = 1024 * 8;

    if (argc != 3) {
        printf("Usage: %s source_file target_file\n", argv[0]);
        return 1;
    }

    source = fopen(argv[1], "rb");
    dest   = fopen(argv[2], "wb");

    if (!source || !dest) {
        perror("File error");
        return 1;
    }

    buffer = malloc(bufsize);
    if (!buffer) {
        perror("Memory allocation failed");
        return 1;
    }

    while ((bytes = fread(buffer, 1, bufsize, source)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    free(buffer);
    fclose(source);
    fclose(dest);

    return 0;
}
