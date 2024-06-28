#include <iostream>
#include <fstream>
#include "../include/compiler.hpp"

int main()
{
  int ptr = 0;
  std::ofstream output("debug_asm.S");
  std::map<string, int> var_table;
  output << asm_getters::base_template();
  operations::declare_variable(output, var_table, "a", 5, ptr);
  operations::print_variable(output, var_table, "a", ptr);
  output << asm_getters::end_program();
}
