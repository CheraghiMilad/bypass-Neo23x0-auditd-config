#define _GNU_SOURCE
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/mount.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#ifndef __NR_open_tree
#define __NR_open_tree 428
#endif
#ifndef __NR_move_mount
#define __NR_move_mount 429
#endif

int main() {
    int fd;
    const char *source_path = "/proc";
    const char *target_path = "/tmp/proc_copy";

    if (mkdir(target_path, 0755) == -1 && errno != EEXIST) {
        perror("mkdir failed");
        return 1;
    }

    fd = syscall(__NR_open_tree, AT_FDCWD, source_path, OPEN_TREE_CLONE | AT_RECURSIVE);
    if (fd == -1) {
        perror("open_tree failed");
        return 1;
    }
    printf("open_tree succeeded, fd = %d\n", fd);

    if (syscall(__NR_move_mount, fd, "", AT_FDCWD, target_path, MOVE_MOUNT_F_EMPTY_PATH) == -1) {
        perror("move_mount failed");
        close(fd);
        return 1;
    }

    printf("Successfully cloned and mounted '%s' to '%s'\n", source_path, target_path);
    close(fd);
    return 0;
}