#include <stdio.h>
#include <sys/klog.h> 
#include <errno.h>
#include <string.h>

int main() {
    int ret = syslog(5 /* SYSLOG_ACTION_CLEAR */, NULL, 0);
    if (ret == -1) {
        perror("syslog SYSLOG_ACTION_CLEAR failed");
        return 1;
    }
    printf("Kernel log buffer cleared successfully.\n");
    return 0;
}
