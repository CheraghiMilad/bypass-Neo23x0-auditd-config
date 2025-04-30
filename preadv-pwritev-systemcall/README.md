## Bypassing the Neo23x0 (Florian Roth) auditd Configuration Using the preadv and pwritev systemcalls.


I use the preadv and pwritev systemcalls to read and write without any evidens.

#### preadv and pwritev System Calls in Linux

The preadv and pwritev system calls are advanced I/O operations available in Linux (and other UNIX-like systems) that allow reading and writing from or to a file descriptor using multiple buffers (scatter/gather I/O). They are extensions of the pread and pwrite system calls, combining them with the functionality of readv and writev.

preadv performs a positioned read into multiple buffers specified by an array of iovec structures. Each iovec defines a memory region to read into. The call reads data starting at a specified offset in the file, without changing the file descriptor's internal offset. This is particularly useful in multi-threaded applications where threads need to read from specific file locations concurrently, without interfering with each other.

Similarly, pwritev writes data from multiple buffers to a given offset in a file, again without altering the file descriptor’s current position. This atomic behavior enables efficient and thread-safe file writing, especially for large or structured data where segments are logically separated in memory.

Both system calls take the following form:

ssize_t preadv(int fd, const struct iovec *iov, int iovcnt, off_t offset);
ssize_t pwritev(int fd, const struct iovec *iov, int iovcnt, off_t offset);

They return the number of bytes read or written, or -1 on error. These calls are part of the _GNU_SOURCE feature set and require #define _GNU_SOURCE before including headers to use them.

In practice, preadv and pwritev are ideal for efficient high-performance I/O operations in databases, file servers, and sandboxed environments where direct control over file offsets and buffer layout is essential.


[You can see the PoC here]()
