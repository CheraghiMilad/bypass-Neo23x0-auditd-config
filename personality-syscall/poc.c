#include <stdio.h>
#include <sys/personality.h>

int main() {
    // Get current personality
    unsigned long old = personality(0xFFFFFFFF);
    printf("Current personality: 0x%lx\n", old);

    // Set new personality: Disable ASLR
    if (personality(old | ADDR_NO_RANDOMIZE) == -1) {
        perror("personality");
        return 1;
    }

    printf("ASLR disabled for this process.\n");

    // Run some code here to observe the impact
    return 0;
}
