#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "lineread.h"

/**
 * This simple main() implementation demonstrates how lineread() should work --
 * it opens a file and prints out each line separately.
 */
int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: read_file filename\n");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    ssize_t read_sz;
    unsigned long counter = 0;

    while (true) {
        char buf[64] = { 0 };
        read_sz = lineread(fd, buf, 63);
        if (read_sz <= 0) {
            break;
        }
        printf("Read %lu, bytes: %zu | %s\n", counter, read_sz, buf);
    }

    return 0;
}