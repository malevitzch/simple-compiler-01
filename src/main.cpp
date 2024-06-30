#include <iostream>
#include <fstream>
#include "../include/compiler.hpp"

int main()
{
  std::ofstream output("debug_asm.S");
  std::map<string, int> var_table;
  Compiler compiler(output);
  output << asm_getters::base_template();
  compiler.add_operation(new DeclarationOperation("a", 1));
  compiler.add_operation(new DeclarationOperation("b", 1));
  compiler.add_operation(new DeclarationOperation("c", 1));
  compiler.add_operation(new AssignmentOperation("a", -2366));
  compiler.add_operation(new PrintOperation("a"));
  compiler.add_operation(new PrintOperation("c"));
  compiler.process_all();
  output << asm_getters::end_program();
  //test program that prints the values of a and c
}
