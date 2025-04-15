# minishell

Welcome to **minishell**, a simple Unix shell developed in C as part of the 42 curriculum. This project is about replicating the behavior of a real shell — parsing, executing commands, handling environment variables, and managing signals.

---

## Project Overview

`minishell` implements a subset of bash shell features:
- Displaying a prompt and reading user input
- Tokenizing and parsing commands
- Executing binaries with arguments and environment
- Handling built-in commands (`cd`, `pwd`, `export`, `unset`, `env`, `echo`, `exit`)
- Pipes (`|`), redirections (`>`, `<`, `>>`, `<<`)
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Quote handling (`'`, `"`)
- Environment variable expansion (`$VAR`, `$?`)
- Heredocs

---

## Installation & Usage

### Dependencies

Make sure you have [readline](https://tiswww.case.edu/php/chet/readline/rltop.html) installed.  
If you're on macOS using Homebrew, run:

```bash
brew install readline
```
### Building the Shell
Clone the repository and run:
```bash
make
```
### Running minishell
Once compiled, start the shell with:
```bash
./minishell
```
✨ Then start typing your commands just like you would in bash!



### Built-in Commands
Command | Description
echo | Print arguments to the standard output
cd | Change the current working directory
pwd | Print the current working directory
export | Set environment variables
unset | Remove environment variables
env | Display the current environment
exit | Exit the shell



### Features
✅ Input parsing and tokenization

✅ Heredoc (<<)

✅ Pipes and redirections

✅ Environment variable handling

✅ Return code $? support

✅ Signal management (Ctrl+C, Ctrl+)



### Project Structure
minishell/ ├── builtins/ # Built-in command implementations
├── execution/ # Execution engine and redirections
├── lexer/ # Lexical analysis
├── parser/ # Command parsing
├── tokenizer/ # Tokenization helpers
├── sources/ # Main source files and utils
├── Makefile # Build system
└── README.md # This file!


### Bonus Ideas

✅ Implement wildcard expansion (*)


## 🧑‍💻 Authors

- **Kaltoum** – [@banditklm](https://github.com/banditklm)
- **soufiane** – [@soufiixarif](https://github.com/soufiixarif)







