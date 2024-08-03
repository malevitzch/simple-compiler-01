# simple-compiler-01
An attempt at making a very simple compiler.
The initial goal of this project is to create a simple, not necessarily turing-complete programming language which will compile to x86-64 nasm assembly and support the following operations:
- decl [name] [expr]; (which declares a 32-bit integer variable with the specified name and assigns it like in c, for example decl x = y+z; is valid)
- print [name]; (which prints the value of the 32-bit integer variable with specified name)])
- [expr] evaluates the expression, usually used with = operator so that the expression does anything
TODO:
- provide a reasonable and convenient command to compile files
- change the way errors are handled (to a polymorphic error class rather than a vector of strings, at the very least)
- implement expression verification (stuff like "x = 2 3 +" still compiles because there the shunting yard algorithm does not check for most expression ordering errors)
