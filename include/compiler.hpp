#pragma once
#include <iostream>
#include <map>
using std::string;
using std::ostream;
<<<<<<< HEAD

=======
bool is_variable_registered(const std::map<string, int>& variable_table, const string name);
//Registers variable in the specified variable table with set name and value, increments the stack ptr by 1. If a variable of the specified value is 
bool register_variable(std::map<string, int>& variable_table, const string name, const int value, int& stack_ptr);
>>>>>>> origin/main
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
