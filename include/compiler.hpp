#include <iostream>
#include <map>
#include <variant>
using std::string;


//Registers variable in the specified variable table with set name and value, increments the stack ptr by 1. If a variable of the specified value is 
std::variant<int, string> register_variable(std::map<string, int>& variable_table, const string name, const int value, int& stack_ptr);

//get
std::variant<int, string> get_variable_value(const std::map<string, int>& variable_table, const string name, const int stack_ptr); 

bool set_variable_value(const std::map<string, int>& variable_table, const string name, const int value, const int stack_ptr);
