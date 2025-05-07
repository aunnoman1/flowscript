# FlowScript Compiler

This project is a compiler for FlowScript, a small, custom scripting language. The compiler takes FlowScript (`.fs`) files as input, parses them, and generates LLVM Intermediate Representation (IR) code (`.ll` files). This LLVM IR can then be compiled into a native executable.

## FlowScript Language Features

FlowScript is designed with a pipeline-oriented programming style. Key features include:

*   **Variable Assignments:** `myVar = 10`
*   **Pipelines:** `expression |> function_call_like |> ...` (output of left becomes input to right)
*   **Built-in Functions:**
    *   `double()`: Multiplies input by 2.
    *   `add(number)`: Adds `number` to the input.
    *   `print()`: Prints the input value.
    *   `print(expression)`: Prints the result of the given expression.
*   **Conditional Statements (`if`/`else`):**
    *   Standard: `if condition_expression { ... } else { ... }`
    *   Piped: `value |> if > compare_value { ... } else { ... }` (also supports `<`, `==`, `!=`)
*   **Loops:** `range(start, end) |> for each { pipeline_statement }`
*   **Integer Arithmetic:** Basic arithmetic operations (`+`, `-`, `*`, `/`) are supported.
*   **Comments:** Single-line comments start with `//`.

## Prerequisites

To build and run this project, you will need:

*   **Flex:** For lexical analysis.
*   **Bison:** For parsing.
*   **Clang or GCC:** A C compiler (Clang is recommended for compiling the generated `.ll` files).
*   **LLVM Development Libraries:** Required for compiling the compiler itself and for `llc`/`clang` to process LLVM IR. Ensure `llvm-config` is in your PATH and points to a compatible LLVM version.

## Build Instructions

The project uses a `Makefile` to manage the build process.

1.  **Build the FlowScript Compiler:**
    ```bash
    make
    # or
    make flowscript_compiler
    ```
    This will create the `flowscript_compiler` executable in the root directory.

## Compiling and Running FlowScript Code

There are a few ways to compile and run FlowScript (`.fs`) files:

**Method 1: Manual Steps**

1.  **Generate LLVM IR (`.ll` file):**
    Use the compiled `flowscript_compiler` to process your `.fs` file. The compiler reads from `stdin` by default if no file is provided as an argument, or it can take a file path. The LLVM IR is written to `output.ll`.
    ```bash
    ./flowscript_compiler < your_script.fs
    # or if your_script.fs is the first argument (as per flowscript_compiler.c)
    # ./flowscript_compiler your_script.fs 
    ```
    This will create an `output.ll` file.

2.  **Compile LLVM IR to an Executable:**
    Use `clang` (recommended) or `llc` + a C linker to compile `output.ll` into a native executable.
    ```bash
    clang output.ll -o my_executable
    ```

3.  **Run the Executable:**
    ```bash
    ./my_executable
    ```

**Method 2: Using Makefile Targets (for `test.fs`)**

The `Makefile` includes convenience targets for compiling and running the `test.fs` file provided in the repository.

1.  **Build Compiler, Generate LLVM IR, and Compile to Executable:**
    This command will perform all necessary steps to create an executable named `test_fs_executable` from `test.fs`.
    ```bash
    make build_test_executable
    ```

2.  **Build and Run the Test Executable:**
    This command does everything `build_test_executable` does, and then runs `test_fs_executable`, printing its output.
    ```bash
    make run_test
    ```
    The output can be compared against the "Expected" comments in `test.fs`.

## Cleaning Up

To remove all generated files (compiler, object files, `output.ll`, executables):

```bash
make clean
```

## Project Structure Overview

*   `flowscript.l`: Lexer definition (Flex).
*   `flowscript.y`: Parser definition (Bison).
*   `ast.h`, `ast.c`: Abstract Syntax Tree structures and functions.
*   `codegen.h`, `codegen.c`: LLVM IR code generation logic.
*   `flowscript_compiler.c`: Main driver for the compiler.
*   `Makefile`: Build script.
*   `test.fs`: An example FlowScript file with various language features and expected outputs.
*   `output.ll`: Default name for the generated LLVM IR file.
*   `README.md`: This file. 