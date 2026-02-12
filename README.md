# Pipex

A Unix pipe simulation program that mimics shell pipe behavior between two commands.

## 📋 Description

**Pipex** is a 42 School project that introduces to the fundamentals of Unix processes, pipes, and file descriptors. The goal is to recreate the behavior of shell pipes by implementing inter-process communication in C.

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)

This project demonstrates:

- **Process creation** with `fork()`
- **Inter-process communication** using pipes
- **File descriptor manipulation** with `dup2()`
- **Command execution** with `execve()`
- **File I/O** operations

The program mimics the following shell behavior:
```bash
< file1 cmd1 | cmd2 > file2
```

Which is equivalent to:
```bash
./pipex file1 cmd1 cmd2 file2
```

**This project was completed as part of the 42 School curriculum.**

## ✨ Features

### Mandatory Part
- **Pipe simulation** - Connects two commands via pipe
- **Input redirection** - Reads from input file
- **Output redirection** - Writes to output file
- **Command execution** - Executes commands with arguments
- **PATH resolution** - Finds executables in PATH
- **Error handling** - Proper error messages and exit codes
- **Memory management** - No memory leaks

### Bonus Features
- **Multiple pipes** - Handles unlimited number of commands
- **Here_doc** - Supports `<<` heredoc syntax
- **Command chaining** - Pipes multiple commands together

## 🔧 Installation

### Prerequisites
- GCC or Clang compiler
- Make
- Unix/Linux or macOS environment

### Compilation

Clone the repository and compile:
```bash
git clone https://github.com/clothildesc/42_pipex.git
cd 42_pipex
make
```

This generates the `pipex` executable.

**Bonus version:**
```bash
make bonus
```

This generates the `pipex_bonus` executable with support for multiple pipes and heredoc.

### Make Commands
- `make` or `make all` - Compile mandatory version
- `make bonus` - Compile bonus version
- `make clean` - Remove object files
- `make fclean` - Remove object files and executables
- `make re` - Recompile everything from scratch

## 💻 Usage

### Basic Usage

**Mandatory version:**
```bash
./pipex infile "cmd1" "cmd2" outfile
```

This behaves like:
```bash
< infile cmd1 | cmd2 > outfile
```

### Examples

**Example 1: Basic pipe**
```bash
./pipex infile "ls -l" "wc -l" outfile
```
Equivalent to:
```bash
< infile ls -l | wc -l > outfile
```

**Example 2: Text processing**
```bash
./pipex input.txt "grep hello" "wc -w" output.txt
```
Equivalent to:
```bash
< input.txt grep hello | wc -w > output.txt
```

**Example 3: With shell commands**
```bash
./pipex file1 "cat" "tr 'a-z' 'A-Z'" file2
```
Converts lowercase to uppercase.

### Bonus Usage

**Multiple pipes:**
```bash
./pipex_bonus infile "cmd1" "cmd2" "cmd3" "cmd4" outfile
```
Equivalent to:
```bash
< infile cmd1 | cmd2 | cmd3 | cmd4 > outfile
```

**Heredoc:**
```bash
./pipex_bonus here_doc LIMITER "cmd1" "cmd2" outfile
```
Equivalent to:
```bash
cmd1 << LIMITER | cmd2 >> outfile
```

Example:
```bash
./pipex_bonus here_doc EOF "grep hello" "wc -l" output.txt
hello world
hello again
EOF
```

## 🏗️ Technical Implementation

### Process Flow

```
Parent Process
     ↓
   fork()
     ↓
   ┌─────────────┬─────────────┐
   │             │             │
Child 1       Parent       Child 2
   │             │             │
dup2(infile)    pipe()     dup2(outfile)
dup2(pipe[1])              dup2(pipe[0])
   │                           │
execve(cmd1)              execve(cmd2)
   │                           │
   └───────→ pipe ←────────────┘
```

## 🧪 Testing

### Test Cases

**Valid commands:**
```bash
./pipex infile "ls -l" "wc -l" outfile
./pipex infile "cat" "grep test" outfile
./pipex infile "cat" "cat" outfile
```

**Edge cases:**
```bash
# Non-existent input file
./pipex nonexistent "cat" "wc -l" outfile

# Invalid command
./pipex infile "invalid_cmd" "wc -l" outfile

# No permissions
./pipex noperm_file "cat" "wc" outfile

# Empty file
./pipex empty.txt "cat" "wc -l" outfile
```

**Compare with shell:**
```bash
# Using pipex
./pipex input "cmd1" "cmd2" output_pipex

# Using shell
< input cmd1 | cmd2 > output_shell

# Compare results
diff output_pipex output_shell
```

### Bonus Tests

**Multiple pipes:**
```bash
./pipex_bonus in "cat" "grep a" "wc -l" "cat" out

# Compare with shell
< in cat | grep a | wc -l | cat > out_shell
diff out out_shell
```

**Heredoc:**
```bash
./pipex_bonus here_doc EOF "cat" "wc -l" out
line 1
line 2
line 3
EOF

# Compare with shell
cat << EOF | wc -l > out_shell
line 1
line 2
line 3
EOF
diff out out_shell
```

## 👥 Author

**Clothilde** (cscache)
- GitHub: [@clothildesc](https://github.com/clothildesc)

## 📖 References

- [Unix Pipes](https://en.wikipedia.org/wiki/Pipeline_(Unix))
- [fork() man page](https://man7.org/linux/man-pages/man2/fork.2.html)
- [pipe() man page](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [execve() man page](https://man7.org/linux/man-pages/man2/execve.2.html)
- [dup2() man page](https://man7.org/linux/man-pages/man2/dup.2.html)

## 📄 License

This project is part of the 42 School curriculum.

---

*Built with 🧠 at 42 School*
