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

This will build the mish for you. Then to run the predefined tests from ostep-project:

```sh
chmod +x run-tests.sh
./run-test.sh
```


