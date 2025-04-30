
## Bypassing the Neo23x0 (Florian Roth) auditd Configuration Using the move_mount and open_tree syscalls.

I use the move_mount and open_tree syscalls to clone and mount /proc to /tmp.

location (e.g., /tmp/proc_copy) using the open_tree and move_mount syscalls, which are available in recent Linux kernel versions.

The program begins by ensuring the target directory (/tmp/proc_copy) exists, creating it if necessary. It then invokes the open_tree syscall with the OPEN_TREE_CLONE and AT_RECURSIVE flags to create a clone of the /proc mount point. This operation returns a file descriptor representing the mount tree.

Next, the move_mount syscall is used to attach the cloned mount tree to the new location. This is done without the need for traditional mount operations, which may be more closely monitored by system audit mechanisms like auditd.

By remounting /proc in this way, it's possible to interact with a fresh view of system process information from an alternate path, potentially bypassing security monitoring tools that are only watching standard paths or classic syscalls.

This technique highlights the need for security configurations and auditing rules to consider newer kernel features and syscalls that may be leveraged to perform privileged operations in unconventional ways.

[You can see the PoC here](https://youtu.be/QnwNuHu15C8?si=bXoxMp4Axj_nFHBI)


