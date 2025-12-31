## 🐚 My Custom Shell (System Programming Project)

**My Custom Shell** is a lightweight Unix-like command-line shell implemented in **C** using **Linux system calls**.
This project is developed as part of a **System Programming** course to understand how real shells work internally, including command parsing, process creation, signal handling, file operations, redirection, and piping.

The shell supports both **built-in commands** and **external Linux commands**, closely mimicking basic behavior of the Linux terminal.

---

## ✨ Features

### 🔹 Core Shell Functionality

* Interactive command prompt (REPL loop)
* Command parsing and tokenization
* Graceful handling of `Ctrl+C` using signals
* Clean exit without crashing

### 🔹 Built-in Commands

* `cd` – change directory
* `exit` – exit the shell
* `ls` – list directory contents

  * Supports `ls -l` (detailed view similar to Linux)
* `cat` – display or create files
* `cp` – copy files

### 🔹 File System Operations

* Uses low-level Linux system calls:

  * `open()`, `read()`, `write()`, `close()`
  * `stat()`, `lstat()`
  * `opendir()`, `readdir()`

### 🔹 Output Redirection

* Supports `>` for redirecting standard output

  ```bash
  ls > output.txt
  cat file.txt > newfile.txt
  ```

### 🔹 Pipes

* Supports single pipe `|`

  ```bash
  ls | grep .c
  cat file.txt | grep hello
  ```

### 🔹 Process Management

* Uses `fork()`, `execvp()`, and `wait()`
* Built-ins run in parent process
* External commands run in child processes

---

## 🧠 Technical Concepts Used

* Linux system calls
* Process creation (`fork`)
* Program execution (`execvp`)
* Inter-process communication (`pipe`)
* File descriptor duplication (`dup2`)
* Signal handling (`SIGINT`)
* Directory and file metadata (`stat`, `lstat`)
* Modular project structure

---

## 📂 Project Structure

```
my_custom_shell/
├── include/
│   └── shell.h
├── src/
│   ├── main.c
│   ├── parser.c
│   ├── signals.c
│   ├── execute.c
│   ├── redirection.c
│   ├── pipe.c
│   ├── builtins/
│   │   └── cd.c
│   └── filesystem/
│       ├── ls.c
│       ├── cat.c
│       └── cp.c
└── Makefile
```

---

## ⚙️ Compilation

Compile the shell using:

```bash
gcc -Wall -Wextra -std=gnu99 \
src/main.c src/parser.c src/signals.c \
src/execute.c src/redirection.c src/pipe.c \
src/builtins/cd.c \
src/filesystem/ls.c src/filesystem/cat.c src/filesystem/cp.c \
-o myshell
```

Run the shell:

```bash
./myshell
```

---

## 🎯 Learning Outcomes

* Understanding how Unix shells work internally
* Hands-on experience with system calls
* Process control and file descriptor management
* Building a modular and extensible system-level project in C

---

## 🚀 Future Enhancements

* Input redirection `<`
* Multiple pipes (`a | b | c`)
* Command history stored in a file
* Environment variable expansion
* Background execution (`&`)

---

## 👩‍💻 Author

**Youmna Saifullah**
System Programming Project
=

Just tell me 🌟
