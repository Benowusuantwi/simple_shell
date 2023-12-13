# Simple Shell Project
This is a simple UNIX command line interpreter, or shell, developed in C as part of a programming project. The shell is designed to replicate basic functionalities of the sh shell.

## Description
This shell was developed to perform basic command executions, display prompt, and handle errors. It provides a simple interface where users can execute single-word commands.

## Features
Interactive Mode: Display a prompt and wait for the user to enter a command.
Command Execution: Executes commands entered by the user.
Error Handling: Displays appropriate error messages for command execution failures.
Ctrl+D Handling: Handles the "end of file" condition when pressing Ctrl+D.
Non-Interactive Mode: Accepts commands from standard input.

## Compilation
Compile the shell using the provided gcc command:
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o ...

### Contributors
This project was done by Benjamin and Maureen
