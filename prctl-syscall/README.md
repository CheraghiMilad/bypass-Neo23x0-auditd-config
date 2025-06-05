# Process Masquerading with `prctl()`

This simple C program demonstrates **process masquerading** by changing its visible name to a fake one using the `prctl()` syscall. This is commonly used in Linux-based systems to disguise a process, potentially for legitimate purposes (like debugging) — or, more nefariously, to hide malicious activity.

## 🧠 What This Code Does

1. **Changes the process name** shown in tools like `htop` or `ps` to a fake name (`kworker/u8:3`), using `prctl()`.
2. **Overwrites `argv[0]`** to replace the original command-line invocation with the fake name, as seen in `/proc/self/cmdline`.
3. **Cleans up the rest of `argv[]`** to reduce visibility of the original command-line arguments.
4. **Keeps the process running** (by sleeping forever) so that it can be observed in system tools.

## 🔍 Why Use `prctl()`?

The `prctl()` function is used to manipulate various characteristics of the calling process. It is defined in `<sys/prctl.h>`.

In this example, the following is used:

```c
prctl(PR_SET_NAME, fake_name, 0, 0, 0);
```

This sets the **process name** as displayed in tools like `htop`, `top`, or within `/proc/[pid]/status`. This is **not** the same as the command-line invocation (`argv[0]`), which is separately overwritten.

### 📖 `prctl(PR_SET_NAME)` Summary

* **Header**: `<sys/prctl.h>`
* **Prototype**: `int prctl(int option, unsigned long arg2, unsigned long arg3, unsigned long arg4, unsigned long arg5);`
* **Usage**: `prctl(PR_SET_NAME, (unsigned long) name)`
* **Effect**: Changes the process name (limited to 15 characters) for display in `/proc` and monitoring tools.

---

## ⚠️ Abuse and Detection

### 🢨 How Attackers Might Abuse This

Malware or red teamers can use this technique to:

* Disguise a malicious process as a **legitimate system daemon**, like `kworker`, `cron`, or `bash`.
* Hide their activity from naive system administrators or casual process monitoring.
* Confuse defenders and incident responders during triage or threat hunting.

This is often combined with **other evasion techniques** such as:

* Hiding in `/tmp`, `/dev/shm`, or custom mount namespaces.
* Running under a stolen or unused user account.
* Packing/binary obfuscation to evade detection tools.

### 🛡️ How Defenders Can Detect This

* **Compare `/proc/[pid]/comm` vs `/proc/[pid]/cmdline`**: Inconsistencies between process name and command-line can be suspicious.
* **Monitor for known fake names** (e.g., `kworker`, `sshd`) appearing in unexpected contexts or owned by the wrong user.
* Use **Sysmon for Linux**, **auditd**, or **eBPF** tools to track suspicious process behavior.
* Look for long-running "worker" or "idle"-looking processes doing unusual actions (e.g., network access, file drops).

---

## 🧪 Example Output

After compiling and running:

```bash
gcc masquerade_poc.c -o masquerade
./masquerade
```

The process may appear like this in `htop` or `ps`:

```
kworker/u8:3
```

But a deeper look at `/proc` may reveal the deception:

```bash
cat /proc/$(pidof masquerade)/cmdline
# Might show altered command-line or null bytes
```

---

## 🛠️ Compile and Run

```bash
gcc masquerade_poc.c -o masquerade
./masquerade
```

To stop the process:

```bash
kill $(pidof masquerade)
```

---

## ⚠️ Disclaimer

This code is provided **for educational and research purposes only**. Use responsibly and only in controlled environments or labs. Unauthorized use on production systems or systems you do not own is illegal and unethical.

---

## 📚 References

* [`prctl(2)` man page](https://man7.org/linux/man-pages/man2/prctl.2.html)
* [Linux process memory layout: `/proc/[pid]/comm`, `/cmdline`, `/status`](https://man7.org/linux/man-pages/man5/proc.5.html)
* Threat detection resources from MITRE ATT\&CK: [T1036.004 - Masquerading: Masquerade Task or Service](https://attack.mitre.org/techniques/T1036/004/)
