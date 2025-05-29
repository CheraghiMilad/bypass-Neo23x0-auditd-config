# Linux `sysinfo()` Syscall

This `poc` demonstrates how to use the Linux `sysinfo()` syscall in C to retrieve real-time system information such as memory usage, uptime, load averages, and more.

---

## 🧠 What is `sysinfo()`?

The `sysinfo()` syscall provides a snapshot of system-wide statistics in a single syscall. It is defined in `<sys/sysinfo.h>` and internally uses syscall number **99** on x86_64 Linux (as of kernel 5.x+).

It's efficient and low-level, avoiding the need to parse files like `/proc/meminfo` or `/proc/loadavg`.

---

## 📦 What Does It Return?

The syscall fills a `struct sysinfo`:

```c
struct sysinfo {
    long uptime;             // Seconds since boot
    unsigned long loads[3];  // Load averages (1, 5, 15 min) scaled by 1<<16
    unsigned long totalram;  // Total usable RAM
    unsigned long freeram;   // Available RAM
    unsigned long sharedram; // Shared memory (legacy)
    unsigned long bufferram; // Memory used by buffers
    unsigned long totalswap; // Total swap space
    unsigned long freeswap;  // Free swap space
    unsigned short procs;    // Number of current processes
    unsigned long totalhigh; // Total high memory (if present)
    unsigned long freehigh;  // Free high memory
    unsigned int mem_unit;   // Memory unit size in bytes
    char _f[20 - 2 * sizeof(long) - sizeof(int)]; // Padding (ignore)
};
