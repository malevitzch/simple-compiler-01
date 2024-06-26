# simple-compiler-01
An attempt at making a very simple compiler.
The initial goal of this project is to create a simple, not necessarily turing-complete programming language which will compile to x86-64 nasm assembly and support the following operations:
- DECL [name] [value] (which declares a 64-bit integer variable with the specified name and value)
- PRINT [name] (which prints the value of the 64-bit integer variable with specified name)
- SET [name] [value] (which sets the value of an already declared variable with the specified name)

