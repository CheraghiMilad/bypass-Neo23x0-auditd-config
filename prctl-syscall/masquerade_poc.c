#define _GNU_SOURCE
#include <sys/prctl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
    const char *fake_name = "kworker/u8:3";

    // Step 1: Set process name using prctl (shown in tools like htop)
    prctl(PR_SET_NAME, fake_name, 0, 0, 0);

    // Step 2: Overwrite argv[0] if it has enough space
    size_t original_len = strlen(argv[0]);
    size_t fake_len = strlen(fake_name);

    if (fake_len <= original_len) {
        // Replace argv[0] contents
        memset(argv[0], 0, original_len);
        strncpy(argv[0], fake_name, original_len);
    } else {
        // Prevent overrun (or handle dynamically with /proc/self/mem, etc.)
        fprintf(stderr, "Fake name too long for argv[0], skipping overwrite.\n");
        return 1;
    }

    // Step 3: Clear remaining argv arguments to hide clues
    for (int i = 1; i < argc; i++) {
        memset(argv[i], 0, strlen(argv[i]));
    }

    // Keep process running so it can be observed
    while (1) {
        sleep(10);
    }

    return 0;
}
