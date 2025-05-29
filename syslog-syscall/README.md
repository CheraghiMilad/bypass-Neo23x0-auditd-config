# Using the `syslog` Syscall to Clear Kernel Log Buffer in Linux

This repository contains a simple C program demonstrating how to clear the Linux kernel ring buffer (commonly accessed via `dmesg`) by invoking the `syslog` syscall with the action `SYSLOG_ACTION_CLEAR`.

---

## About the Code

The program calls the `syslog` syscall with the action code `5` (`SYSLOG_ACTION_CLEAR`), which instructs the kernel to clear the entire kernel log buffer. This buffer holds low-level kernel messages visible via the `dmesg` command.

4 # SYSLOG_ACTION_READ_CLEAR : Read and clear log
5 # SYSLOG_ACTION_CLEAR: Clear kernel ring buffer (without reading)
6 # SYSLOG_ACTION_CONSOLE_OFF: Disable logging to console


Required auditd configuration:
        -a always,exit -F arch=b64 -S syslog -F a0=4 -k clear_dmesg_logs
        -a always,exit -F arch=b64 -S syslog -F a0=5 -k clear_dmesg_logs
        -a always,exit -F arch=b64 -S syslog -F a0=6 -k disable_dmesg_logs
        -a always,exit -F arch=b32 -S syslog -F a0=4 -k clear_dmesg_logs
        -a always,exit -F arch=b32 -S syslog -F a0=5 -k clear_dmesg_logs
        -a always,exit -F arch=b32 -S syslog -F a0=6 -k disable_dmesg_logs