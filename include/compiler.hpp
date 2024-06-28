#include <iostream>
#include <map>
using std::string;

bool check_variable_registration(const std::map<string, int>& variable_table, const string name);
//Registers variable in the specified variable table with set name and value, increments the stack ptr by 1. If a variable of the specified value is 
bool register_variable(std::map<string, int>& variable_table, const string name, const int value, int& stack_ptr);

namespace asm_getters
{
  string register_variable(const int value);
  string modify_variable(const int value, const int target_ptr, const int stack_ptr);
  string print_variable(const int target_ptr, const int stack_ptr);
  string base_template();
}
