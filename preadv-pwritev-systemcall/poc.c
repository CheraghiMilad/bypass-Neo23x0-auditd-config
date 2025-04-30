#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/uio.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 1024

int main() {
    const char *input_file = "/etc/passwd";
    const char *output_file = "output_pwritev.txt";

    int fd_in = open(input_file, O_RDONLY);
    if (fd_in < 0) {
        perror("open input");
        return 1;
    }

    int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out < 0) {
        perror("open output");
        close(fd_in);
        return 1;
    }

    char buf1[BUF_SIZE];
    char buf2[BUF_SIZE];

    struct iovec iov[2];
    ssize_t nread;
    off_t offset = 0;

    while (1) {
        iov[0].iov_base = buf1;
        iov[0].iov_len = BUF_SIZE;
        iov[1].iov_base = buf2;
        iov[1].iov_len = BUF_SIZE;

        nread = preadv(fd_in, iov, 2, offset);
        if (nread < 0) {
            perror("preadv");
            break;
        } else if (nread == 0) {
            break; // EOF
        }

        ssize_t nwritten = pwritev(fd_out, iov, 2, offset);
        if (nwritten < 0) {
            perror("pwritev");
            break;
        }

        offset += nread;
    }

    close(fd_in);
    close(fd_out);
    printf("Copy complete using preadv/pwritev.\n");
    return 0;
}
