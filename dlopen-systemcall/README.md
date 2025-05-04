## Bypassing the Neo23x0 (Florian Roth) auditd Configuration Using dlopen systemcall.


This shared object (.so) is a Linux version of a DLL side-loading or preload attack. Instead of running as a standalone executable, it is loaded dynamically by another process or binary. The core idea is to execute custom code automatically when the library is loaded, without requiring any explicit function calls from the target process.

To achieve this behavior, we used the __attribute__((constructor)) attribute in the C code. This attribute tells the compiler to mark the on_load() function to be run immediately upon loading the shared object, before any code in the main binary is executed. This is useful in scenarios where an attacker wants their payload to execute stealthily during the loading of a benign-looking .so file.

The payload in this example reads the contents of /etc/passwd (a common target file in Linux) and writes it to /tmp/output.txt using readv() and writev() system calls, which allow for vectorized I/O operations. Once compiled into a .so file with gcc -fPIC -shared, the attacker can use LD_PRELOAD to inject this shared object into almost any dynamically linked Linux binary (like /bin/ls) and execute the code covertly.

## Compile Commands
gcc -fPIC -shared -o libstealer.so lib-so.c
gcc -o host poc.c -ldl