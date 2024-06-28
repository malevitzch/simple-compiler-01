#pragma once
#include <iostream>
#include <map>
using std::string;
using std::ostream;
bool is_variable_registered(const std::map<string, int>& variable_table, const string name);
//Registers variable in the specified variable table with set name and value, increments the stack ptr by 1. If a variable of the specified value is 
bool register_variable(std::map<string, int>& variable_table, const string name, const int value, int& stack_ptr);
//test comment
class Compiler
{
private:
  ostream& target;
  int stack_ptr = 0;
  std::map<string, int> variable_table;
public:
  Compiler() = delete;
  Compiler(ostream& target);
};

namespace asm_getters
{
  string create_variable(const int value);
  string modify_variable(const int value, const int target_ptr, const int stack_ptr);
  string print_variable(const int target_ptr, const int stack_ptr);
  string base_template();
  string end_program();
}

namespace operations
{
  bool declare_variable(ostream& target, std::map<string, int>& variable_table, const string name, const int value, int& stack_ptr);
  bool assign_to_variable(ostream& target, std::map<string, int>& variable_table, const string name, const int value, const int stack_ptr);
  bool print_variable(ostream& target, const std::map<string, int>& variable_table, const string name, const int stack_ptr);
}

