## Bypassing the Neo23x0 (Florian Roth) auditd Configuration Using the readv and writev systemcalls.

I use the readv and writev systemcalls to read and write /etc/passwd without any evidens as (non-root)

readv and writev — Efficient Scatter/Gather I/O

The readv and writev system calls are part of the POSIX I/O interface and are used for scatter/gather I/O operations. These system calls allow you to read data from a file descriptor into multiple non-contiguous memory buffers (readv), or write data from multiple buffers to a file descriptor (writev). This is often more efficient than making multiple read() or write() calls, especially when working with structured data or networking buffers.

The key idea behind readv is that it allows data to be scattered into multiple buffers with a single system call. You provide an array of struct iovec, each containing a pointer to a buffer and the length of that buffer. The kernel then fills each buffer in order until the requested number of bytes are read, or until the buffers are filled. This reduces the overhead of multiple user-kernel transitions and keeps data in its native structured form without copying it into a single temporary buffer.

Similarly, writev performs the gathering operation by taking multiple buffers and writing them out sequentially to a file descriptor in one call. This is very useful when constructing responses for sockets or writing structured logs or files, as it avoids concatenating data into a temporary buffer before writing. It also makes the code cleaner and easier to maintain by separating different pieces of data logically in memory.

These system calls are particularly useful in performance-critical applications such as network servers, databases, or sandboxing systems where you want to minimize syscalls and memory copying. However, they are low-level and require precise memory management and buffer coordination. Also, the total number of bytes transferred may be less than the total size of the iovec array, so partial read/writes should always be handled correctly in robust applications.

[You can see the PoC here](https://youtu.be/pPUtbYm8bbo?si=lnBn-6idfo9wIwEE)