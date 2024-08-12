# LC3 VM Testing


## Overview

This project is a virtual machine (VM) written in C that emulates the LC3 (Little Computer 3) architecture. The LC3 is a simple, educational computer architecture used to teach the fundamentals of computer science and assembly language programming.


## Features

- Full implementation of the LC3 instruction set.
- Memory management and register simulation.
- Input/output handling as per LC3 specifications.
- Supports loading and executing LC3 object files.

## Getting Started

### Prerequisites

Ensure you have the following installed on your system:

- GCC (GNU Compiler Collection)
- Make

### Building the Project

To build the VM, run the following command in the project root directory:

```bash
make
```

This will compile all source files and generate an executable named lc3vm.

### Running the VM
To run the VM with an LC3 object file:
```bash
./main [object-file.obj]
```