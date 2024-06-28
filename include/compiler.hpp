#pragma once
#include <iostream>
#include <map>
using std::string;
using std::ostream;

class Compiler
{
private:
  ostream& target;
  int stack_ptr = 0;
  std::map<string, int> variable_table;
  bool is_variable_registered(string name) const;
  bool register_variable(string name, int value);
public:
  Compiler() = delete;
  Compiler(ostream& target);
  bool declare_variable(string name, int value);
  bool assign_to_variable(string name, int value);
  bool print_variable(string name) const;
};

namespace asm_getters
{
  string create_variable(int value);
  string modify_variable(int value, int target_ptr, int stack_ptr);
  string print_variable(int target_ptr, int stack_ptr);
  string base_template();
  string end_program();
}
