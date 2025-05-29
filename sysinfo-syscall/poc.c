#include <stdio.h>
#include <sys/sysinfo.h>

int main() {
    struct sysinfo info;

    if (sysinfo(&info) != 0) {
        perror("sysinfo");
        return 1;
    }

    // Convert load averages from fixed-point (1<<16) to float
    double load1 = (double)info.loads[0] / 65536.0;
    double load5 = (double)info.loads[1] / 65536.0;
    double load15 = (double)info.loads[2] / 65536.0;

    // Convert memory values using mem_unit
    unsigned long mem_unit = info.mem_unit;
    if (mem_unit == 0) mem_unit = 1;  // Just in case

    printf("=== sysinfo ===\n");
    printf("Uptime:             %ld seconds\n", info.uptime);
    printf("Load averages:      %.2f, %.2f, %.2f\n", load1, load5, load15);
    printf("Total RAM:          %lu MB\n", (info.totalram * mem_unit) / (1024 * 1024));
    printf("Free RAM:           %lu MB\n", (info.freeram * mem_unit) / (1024 * 1024));
    printf("Shared RAM:         %lu MB\n", (info.sharedram * mem_unit) / (1024 * 1024));
    printf("Buffer RAM:         %lu MB\n", (info.bufferram * mem_unit) / (1024 * 1024));
    printf("Total Swap:         %lu MB\n", (info.totalswap * mem_unit) / (1024 * 1024));
    printf("Free Swap:          %lu MB\n", (info.freeswap * mem_unit) / (1024 * 1024));
    printf("Number of Processes:%u\n", info.procs);
    printf("Total High Memory:  %lu MB\n", (info.totalhigh * mem_unit) / (1024 * 1024));
    printf("Free High Memory:   %lu MB\n", (info.freehigh * mem_unit) / (1024 * 1024));
    printf("Memory Unit Size:   %u bytes\n", info.mem_unit);

    return 0;
}
