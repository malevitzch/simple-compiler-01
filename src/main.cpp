#include <iostream>
#include <fstream>
#include "../include/compiler.hpp"

int main()
{
  std::ofstream output("debug_asm.S");
  std::map<string, int> var_table;
  Compiler compiler(output);
  output << asm_getters::base_template();
  compiler.declare_variable("b", 1);
  compiler.declare_variable("a", 5);
  compiler.declare_variable("c", 7);
  compiler.assign_to_variable("a", -2366);
  compiler.print_variable("a");
  compiler.print_variable("c");
  output << asm_getters::end_program();
  //test program that prints the values of a and c
}
