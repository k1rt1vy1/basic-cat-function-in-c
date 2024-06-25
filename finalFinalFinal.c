#include <unistd.h>
#include "my_printf.h"
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    char buf[512];
    ssize_t letter = read(0, buf, 512);
    // Reading the Input
    if (letter == -1) {
        my_printf("Error reading input\n");
        return 1;
    }

    if (letter > 0 && letter < 512) {
        buf[letter] = '\0';
    } else if (letter == 512) {
        buf[511] = '\0';
    }

    // Check on format
    if ((buf[0] == 'c') && (buf[1] == 'a') && (buf[2] == 't')) {
        my_printf("Format is correct\n");
    } else {
        my_printf("Invalid Format. Valid format: cat filename.txt\n");
        return 1;
    }

    int sz = letter - 4;
    char *file = (char *)malloc(sz);

    for (int i = 0; i < sz; i++) {
        file[i] = buf[i + 4];
    }
    file[sz - 1] = '\0';

    int fd = open(file, O_RDONLY);
    if (fd == -1) {
        my_printf("File does not exist\n");
        free(file);
        return 1;
    }

    my_printf("File opened successfully\n");

    char content[1000];
    ssize_t bytesRead;
    while ((bytesRead = read(fd, content, sizeof(content) - 1)) > 0) {
        content[bytesRead] = '\0';
        my_printf("%s", content);
    }

    if (bytesRead == -1) {
        my_printf("Error reading file\n");
    }
    if (close(fd) == -1) {
        my_printf("Error closing file\n");
    }

    free(file);
    return 0;
}
