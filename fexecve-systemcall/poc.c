#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    const char *path = "/bin/echo";

    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char *const args[] = { "echo", "Hello from fexecve!", NULL };

    char *const envp[] = { "PATH=/usr/bin:/bin", NULL };

    if (fexecve(fd, args, envp) == -1) {
        perror("fexecve");
        close(fd); 
        exit(EXIT_FAILURE);
    }
    return 0;
}
