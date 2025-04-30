# Bypassing Neo23x0 Auditd Configuration on Linux Systems

Welcome to my cybersecurity research repository, focused on **Linux-based detection engineering, threat simulation, and defense evasion techniques**. This space is dedicated to documenting my journey as I explore real-world attack methods and how to detect, prevent, or analyze them.

---

## 🧠 Purpose

This repository serves as an open notebook for my research in **Linux Blue Teaming**. From hardening audit frameworks like `auditd`, to understanding how attackers bypass them, I aim to contribute back to the community with:

- 🔬 Hands-on Proof-of-Concepts (PoCs)
- 🛡️ Blue team detection strategies
- 🐚 System internals deep dives
- ⚔️ Red vs Blue simulations
- 📓 Practical logging guides and detection references

---

## 🔍 Featured Research

### ▶️ Bypassing Neo23x0 Auditd Configuration on Linux Systems

This PoCs demonstrates how low-level system calls and process manipulation can bypass the default `audit.rules` provided by Neo23x0. It highlights blind spots in many detection setups and suggests ways to improve audit coverage.

> ✅ **Objective:** Reveal gaps in audit-based detection  
> ❌ **What it’s not:** A tool for malicious use

---

## 🧩 Current Topics I’m Working On

- [ ] Linux kernel-level logging gaps
- [ ] Detecting Linux shellcode injections
- [ ] Tracking sudo abuse with auditd & Zeek
- [ ] Writing Sigma rules for Linux TTPs
- [ ] Forensic-ready logging in containerized environments

---

## 📦 How to Use This Repository

Each folder contains a focused project with:
- ✅ A `README.md` explaining the objective
- 💥 A PoC (`*.sh`, `*.c`, `*.py`, or Rust)
- 📎 Documentation or references
- 🧪 Notes on detection ideas or bypass methods

---

## 🤝 Contributing

I welcome contributions, ideas, or even constructive criticism. Open an issue or submit a pull request if you have something to add or improve.

---

## 📫 Contact

- Telegram: `@OsSecurityResearcher`
- LinkedIn: [Milad Cheraghi](https://www.linkedin.com/in/miladcheraghi/)

---

## 🛡️ Disclaimer

All content in this repository is for **educational and defensive research purposes only**. Do not use any PoC or script here in unauthorized environments.
