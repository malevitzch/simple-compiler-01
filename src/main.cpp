#include <iostream>
#include <fstream>
#include "../include/compiler.hpp"

int main()
{
  std::ofstream output("debug_asm.S");
  std::map<string, int> var_table;
  Compiler compiler(output);
  output << asm_getters::base_template();
  compiler.add_operation(DeclarationOperation("a", 1));
  compiler.add_operation(DeclarationOperation("b", 1));
  compiler.add_operation(DeclarationOperation("c", 1));
  compiler.add_operation(AssignmentOperation("a", -2366));
  compiler.add_operation(PrintOperation("a"));
  compiler.add_operation(PrintOperation("c"));
  compiler.process_all();
  output << asm_getters::end_program();
  //test program that prints the values of a and c
}
