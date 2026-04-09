*This project has been created as part of the 42 curriculum by gkryszcz and emurbane .*

# Minishell

## Description
**Minishell** is a project in the 42 school curriculum focused on creating a simple shell inspired by Bash. The goal is to hande file descriptors, manage processes, have a working history and have basic Bash-like functionalities. It is a great way to learn C programming, memory management, and system architecture.

## Features
Our shell successfully replicates the following core Bash functionalities:
* **Prompt & History:** Displays a custom prompt and stores command history using the `readline` library.
* **Execution:** Locates and executes programs using the `PATH` environment variable, as well as relative and absolute paths.
* **Lexing & Parsing:** Correctly interprets spaces, words, and other symbols.
* **Quotes:** * Single quotes (`'`) prevent the interpretation of meta-characters.
  * Double quotes (`"`) prevent interpretation of meta-characters except for the dollar sign (`$`).
* **Redirections:**
  * `<` redirects input
  * `>` redirects output 
  * `>>` redirects output
  * `<<`  reads input until a specified delimiter is seen
* **Pipes (`|`):** Connects the output of one command to the input of the next using pipes.
* **Environment Variables:** Expands `$VAR` to its corresponding value in the environment.
* **Exit Status:** Expands `$?` to the exit status of the most recently executed pipeline.
* **Signals:** Handles `Ctrl-C` (new prompt), `Ctrl-D` (exit), and `Ctrl-\` (ignored) identically to bash.
* **Built-in Commands:**
  * `echo` (with `-n` flag)
  * `cd` (relative/absolute paths)
  * `pwd`
  * `export`
  * `unset`
  * `env`
  * `exit`

## Instructions

### Compilation
The project uses a `Makefile` to compile the source code and the `libft` library.
```bash
# Clone the repository
git clone <your_repository_url>
cd minishell

# Compile the executable
make
./minishell
# To clean up object files and the executable, you can use:
make clean    # Removes object files
make fclean   # Removes object files and the executable
make re       # Recompiles the whole project
```
## Resources
During the development of this project, the following references were used:

GNU Bash Reference Manual: Used to understand the exact expected behavior of edge cases, quotes, and redirections.

Linux Programmer's Manual (man pages): Essential documentation for system calls (fork, execve, pipe, dup2, waitpid, stat, access).

Readline Documentation: For handling the interactive prompt and history memory management.

## Use of AI
Artificial Intelligence  was used throughout this project as a virtual tutor and code-assistant for some tasks, for example:

System Call Architecture: AI was used to explain the theoretical flow and synchronization between fork, pipe, and dup2 when building complex multi-pipe chains.

Norminette Compliance: AI assisted in refactoring large blocks of code to strictly stick to the 42 Norm


Automated Testing: AI was used to generate comprehensive Bash test scripts that allowed us to pipe inputs into both our Minishell and the real Bash, using diff to compare the outputs and ensure 100% accuracy.
