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
  string create_variable(const int value)
  {
    return "\tpush" + std::to_string(value) + "\n"; 
  }
  string modify_variable(const int value, const int target_ptr, const int stack_ptr)
  {
    return "\tmov [rsp+" + std::to_string(8*(stack_ptr-target_ptr)) +"], " + std::to_string(value) + "\n";
  }
  string print_variable(const int target_ptr, const int stack_ptr)
  {
    return "\tpush [rsp+" + std::to_string(8*(stack_ptr-target_ptr)) + "]\n\tadd rsp, 8\n";
  }
  string base_template()
  {
    return "section .text\n\nextern _print\nglobal _start\n\n_start:\n";
  }
}
namespace operations
{
  bool declare_variable(ostream& target, std::map<string, int>& variable_table, const string name, const int value, int& stack_ptr)
  {
    if(!register_variable(variable_table, name, value, stack_ptr)) return false;
    target << asm_getters::create_variable(value);
    return true;
  }
  bool assign_to_variable(ostream& target, std::map<string, int>& variable_table, const string name, const int value, int& stack_ptr)
  {
    if(!is_variable_registered(variable_table, name)) return false;
    target << asm_getters::modify_variable(value, variable_table[name], stack_ptr);
    return true;
  }
  bool print_variable(ostream& target, const std::map<string, int>& variable_table, const string name, int& stack_ptr)
  {
    if(!is_variable_registered(variable_table, name)) return false;
    target << asm_getters::print_variable(variable_table.at(name), stack_ptr);
    return true;
  }
}

