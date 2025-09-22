# simple-compiler-01
An attempt at making a very simple compiler. The project is discontinued but it served as a very interesting excersise in generating assembly and understanding how variables are managed on the stack.\
The initial goal of this project was to create a simple, useless programming language which will compile to x86-64 nasm assembly and support the following operations:
- decl [name] [expr]; (which declares a 32-bit integer variable with the specified name and assigns it like in c, for example decl x = y+z; is valid)
- print [name]; (which prints the value of the 32-bit integer variable with specified name)])
>>>>>>> 4a54505 (Updated README)
- [expr] evaluates the expression, usually used with = operator so that the expression does anything
\
# TODO:
- provide a reasonable and convenient command to compile files
- make print use expression eval rather than requiring a variable name
- change the way errors are handled (to a polymorphic error class rather than a vector of strings, at the very least)
- Add a lot more documentation and clean up code
