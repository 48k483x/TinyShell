# sash :
mini-version of bash ;

# Parsing Commands
The Minishell project parses commands using a lexer and parser combination.
It tokenizes user input into a series of tokens.
The parsing process ensures correct interpretation of command arguments, options, and redirects.

# execution Commands:
- Built-in Commands
```bash
#Prints the current environment variables.
$ env
#Sets environment variables.
$ export KEY=VALUE
#Displays messages to the standard output.
$ echo Hello, Minishell!
#Changes the current working directory.
$ cd /path/to/directory
#Terminates the Minishell.
$ exit
#Prints the current working directory.
$ pwd
#Removes an environment variable.
$ unset KEY
```

- Handling Signals
```BASH
#Interrupts the execution of the current command.
Ctrl+C
#Signals end-of-file, closing the input stream.
Ctrl+D
#Terminates the process and generates a core dump.
Ctrl+\
```
- Pipes
```BASH
#Supports command piping, allowing output from one command to be used as input for another.
$ command1 | command2
```

- Redirections
```BASH
#Supports output and input redirections.
$ command > output.txt
$ command < input.txt
```

- Other Commands
```BASH
Handling with execve.
```

# Usage
Compile the source code and run the executable.
```BASH
$ make
$ ./sash
```