# simple-compiler-01
An attempt at making a very simple compiler.
The initial goal of this project is to create a simple, not necessarily turing-complete programming language which will compile to x86-64 nasm assembly and support the following operations:
- DECL [name] [value] (which declares a 32-bit integer variable with the specified name and value)
- PRINT [name] (which prints the value of the 32-bit integer variable with specified name)])
- ASSIGN [name] [value] (which sets the value of an already declared variable with the specified name)

In the future though, ASSING directive will be scrapped once the = operator is implemented. Additionally, IF ... ENDIF directive is also to be considered as the implementation does not exceed my abilities.

TODO:
- integrate the shunting yard algorithm with the project and expand the project with expressions
- provide a reasonable and convenient command to compile files 
