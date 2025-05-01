[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/im4QPs1l)
# Assignment 4: Optimization Passes
This repository contains example optimization passes to help you get started with your assignment.
These passes can be used either as standalone plugins with `opt`/`clang` or integrated directly into LLVM's optimization pipelines at specified extension points.

## Included Passes
### HelloWorld
- A simple pass that prints "Hello, World!"
- Operates on an entire module
- Preserves all analysis pass results

### OpcodeCounter
- **Analysis pass** that counts opcodes in functions
- Runs on each function
- Registered as an analysis pass for use by other passes
- Integrated into optimization pipelines
- Includes a **print pass** that consumes the analysis results and displays them

### ArithmeticSimplifier
- A **transformation pass** that simplifies:
  - `x * 1` → `x`
  - `x + 0` → `x`
- Runs on each function
- **Does not preserve** analysis pass results

## Building and Running
### Building the Project
1. Create a `build` directory and navigate into it:
   ```sh
   mkdir build && cd build
   ```
2. Configure the project:
   ```sh
   cmake ../
   ```
3. Build all passes:
   ```sh
   make
   ```
4. The compiled passes (shared objects) will be located in `build/lib/`.

### Running a Pass
1. Compile `inputs/hello.c` to LLVM IR with `-O0`:
   ```sh
   clang -O0 -S -emit-llvm inputs/hello.c -o hello.ll
   ```
2. Execute your pass on `hello.ll`:
   ```sh
   opt -load-pass-plugin ./build/lib/lib<PassName>.so -passes="<registered-pass-name>" -S ./inputs/hello.ll
   ```

## Assignment Instructions
1. Implement the **5 new passes** as described in the assignment document, following the same structure as the provided examples.
2. Update `CMakeLists.txt` in the `lib` directory to include your new passes.
3. Create test input files to demonstrate each pass's functionality.

## Resources
- [LLVM New Pass Manager Guide](https://llvm.org/docs/WritingAnLLVMNewPMPass.html)
- [`llvm::PassBuilder` Class Reference](https://llvm.org/doxygen/classllvm_1_1PassBuilder.html)
- [Additional Example Passes](https://github.com/banach-space/llvm-tutor)
