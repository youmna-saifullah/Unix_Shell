# Custom Linux Shell with GTK Administrative GUI

A robust, modular Unix-based shell implementation featuring a professional Graphical User Interface (GUI) built with GTK-3. This project bridges the gap between low-level system programming and modern desktop applications, offering 16+ built-in commands, process management, and I/O redirection.

---

## 👥 Authors & Contributors

This project was developed by:

* **Youmna Saifullah**
* **Maryam Fareed**
* **Beenish Gulana**

---

## 🚀 Features

* **Hybrid Interface:** Supports both traditional terminal-based interaction and a GTK-3 graphical dashboard.
* **16+ Built-in Commands:** Including `ls`, `cd`, `cat`, `cp`, `pwd`, `mkdir`, `rm`, `chmod`, `history`, `export`, `kill`, `echo`, and a comprehensive `man` page system.
* **Advanced Logic:** Full support for **Pipes (`|`)**, **I/O Redirection (`>`, `>>`, `<`)**, and **Signal Handling** (e.g., Ctrl+C protection).
* **System Monitoring:** Integrated GUI button hooks for administrative system oversight.
* **Persistent History:** All commands are logged to a hidden history file for audit trails.

---

## 🛠 Prerequisites & Installation

### 1. Environment Setup (Linux/WSL)

Ensure you have the GTK-3 development libraries and build essentials installed:

```bash
sudo apt update
sudo apt install libgtk-3-dev build-essential gcc

```

### 2. Running GUI on Windows (WSL Users)

Since WSL does not natively render GUIs without a helper, you must use **VcXsrv**.

#### Installing & Configuring VcXsrv:

1. **Download:** [VcXsrv Windows X Server](https://sourceforge.net/projects/vcxsrv/).
2. **Launch Settings:**
* Select "Multiple Windows".
* Set "Display number" to `0`.
* **Crucial:** Check the box **"Disable access control"**.


3. **In your WSL Terminal, run:**
```bash
export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0
# OR if that fails:
export DISPLAY=:0

```



---

## 📂 Project Structure

```text
UNIX_SHELL-MAIN/
├── include/           # Header files (shell.h)
├── src/               
│   ├── gui.c          # GTK Interface Logic
│   ├── execute.c      # Command routing & execution
│   ├── parser.c       # Command line string parsing
│   ├── builtins/      # cd, exit, kill, echo, etc.
│   └── filesystem/    # ls, rm, mkdir, man, etc.
├── .myshell_history   # Hidden history log
└── Makefile           # Automated build script

```

---

## 🔨 Building and Running

To compile the entire project including the GUI, use the following command from the root directory:

```bash
gcc src/gui.c src/execute.c src/parser.c src/pipe.c src/redirection.c src/signals.c src/builtins/*.c src/filesystem/*.c -o myshell_gui -Iinclude $(pkg-config --cflags --libs gtk+-3.0)

```

**Run the Shell:**

```bash
./myshell_gui

```

---

## 📚 Resources & References

The development of this shell was supported by the following resources:

* **GeeksforGeeks:** [Write your own shell in C](https://www.geeksforgeeks.org/making-linux-shell-c/)
* **GTK+ 3 Reference Manual:** [Gtk Widgets and Layouts](https://docs.gtk.org/gtk3/)
* **TutorialsPoint:** [Unix Process Management & System Calls](https://www.tutorialspoint.com/unix/index.htm)
* **VcXsrv Documentation:** [WSL2 GUI Setup Guide](https://github.com/microsoft/WSL/issues/4106)

* **Redirection:** Complex piping logic should be typed in the 'Run' box for full `execute_args` processing.

Would you like me to help you create an automated **Makefile** so you can just type `make` to compile everything instead of that long command?
