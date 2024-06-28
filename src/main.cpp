#include <iostream>
#include <fstream>
#include "../include/compiler.hpp"

int main()
{
  int ptr = 0;
  std::ofstream output("debug_asm.S");
  std::map<string, int> var_table;
  output << asm_getters::base_template();
  operations::declare_variable(output, var_table, "b", 1, ptr);
  operations::declare_variable(output, var_table, "a", 5, ptr);
  operations::declare_variable(output, var_table, "c", 7, ptr);
  operations::assign_to_variable(output, var_table, "a", 17, ptr);
  operations::print_variable(output, var_table, "a", ptr);
  operations::print_variable(output, var_table, "c", ptr);
  output << asm_getters::end_program();
  //test program that prints the values of a and c
}
