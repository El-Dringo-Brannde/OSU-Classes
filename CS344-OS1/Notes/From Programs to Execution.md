## Virtual Memory
- Creates the illusion of unshared exclusive memory

## Running a program
- To run a program, the machine code must be pulled from storage and loaded into memory

## Memory in RAM
- Stack memory and heap memory grow towards each other

# Stack Vs. Heap

- ### Stack
  - Stores automatic variables and function pointers as program runs through each block of code
  - variables cannot be resized
  - memory managed by CPU

- ### Heap
  -  Variables are located manually
  - Heap access is slower than stack
  - memory size is unlimited
  - variables can be resized with `realloc()`


## The compiling process
1. C preprocessor expands macros and takes out comments
2. Compiler checks for errors and generates assembly code
3. Compiler calls the assembler which turns the assembly code to machine code
