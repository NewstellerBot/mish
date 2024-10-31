# MISH (Minerva Shell)

For this project, I have built a simple shell. It supports the built-in functionalities described in `WISH.md`:

- `cd`: changes the current directory
- `path`: it adds directory to path
- `exit`: exits the program with status 0

## Running MISH

To run mish, you need to build it from source. Make sure you have `gcc` and `make` installed.

To compile run make

```sh
make
```

Then, you can simply call `mish` in either the interactive mode or with file.

```sh
./mish 
```

or 

```sh
./mish some_file.txt
```

This will build the mish for you. Then to run the predefined tests from ostep-project:

```sh
chmod +x run-tests.sh
./run-test.sh
```

I have also defined some unit tests for the purpose of testing my own code. To run those test, you can use make

```sh
make tests
make run_tests
```

To clean the directory from executables and object file, you can run 

```sh
make clean
```

which will build and run unit tests for `builtins` and `parser`.

## AI Statement

I have used AI heavily to explain the syntax and inner workings of C. Example prompts include, but are not limited to: 

* How to define `struct` in C?
* What is the difference between `typedef struct` and `struct`?
* How to define a pointer to an arbitrary data type?
* What's the difference between using `strcmp` and using `==`?
* How to use file descriptors for reading in arguments from cli?
* How to replace a character with a string so that the character appears empty? (question about \0)
* How to use `fork()` to run multiple processes conccurently?

I have also used AI to debug my compiler statements. For example, I might use AI to ask the following: 

*Given the error below, can you explain me what does the problem relates to? What could be possible causes? error here*

Last, but not least, I have also used AI to help me write the Makefile. I have defined the source path, unit test files, and source for objects, and asked AI to write the Makefile for building different targets.
