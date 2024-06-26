#include <iostream>
#include "../include/compiler.hpp" 
bool is_variable_registered(const std::map<string, int>& variable_table, const string name)
{
  return variable_table.find(name) == variable_table.end();
}

bool register_variable(std::map<string, int>& variable_table, const string name, const int value, int& stack_ptr)
{
  if(is_variable_registered(variable_table, name))
  {
    return false;
  }
  variable_table[name] = ++stack_ptr;
  return true;
}
namespace asm_getters
{
  string register_variable(const int value)
  {
    return "\tpush dword [" + std::to_string(value) + "]\n"; 
  }
  string modify_variable(const int value, const int target_ptr, const int stack_ptr)
  {
    return "\tmov [rsp+" + std::to_string(4*(stack_ptr-target_ptr)) +"], dword [" + std::to_string(value) + "]\n";
  }
  string print_variable(const int target_ptr, const int stack_ptr)
  {
    return "TODO";
  }
}

