## Bypassing the Neo23x0 (Florian Roth) auditd Configuration Using the pread and pwrite systemcalls.


I use the pread and pwrite systemcalls to read and write without any evidens


This C code is designed to demonstrate reading and writing to a sensitive file, specifically the SSH private key file (~/.ssh/id_rsa), using the system calls pread and pwrite.

Opening the File:
The code begins by attempting to open the id_rsa file using the open() system call in read and write mode (O_RDWR). If the file cannot be opened, the program prints an error message and exits.

Reading from the File:
After opening the file successfully, the program uses pread() to read a chunk of data (up to 512 bytes) from the file. This call does not modify the file offset, meaning subsequent reads would continue from the same point. The contents read are stored in a buffer and printed to the terminal.

Writing to the File:
Next, the program attempts to write a small test string (# test-injection-by-poc) to the end of the file using pwrite(). The pwrite() system call allows writing at a specific offset without changing the file’s current position, which is useful for appending data to a file.

Error Handling:
The code checks for errors at each step, including opening the file, reading from it, and writing to it. If any operation fails, the program prints an error message and exits.

[You can see the PoC here](https://youtu.be/ExjJFdVLU3o?si=8KpFIH16AO5C8czm)
