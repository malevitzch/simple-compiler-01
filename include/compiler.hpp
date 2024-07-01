#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "../include/parser.hpp"
using std::string;
using std::ostream;
class Compiler
{
private:
  std::vector<CompilerOperation*> operations;
  ostream& target;
  int stack_ptr = 0;
  std::map<string, int> variable_table;
  bool is_variable_registered(string name) const;
  bool register_variable(string name, int value);
  bool process_operation(CompilerOperation* operation);
  
public:
  Compiler() = delete;
  Compiler(ostream& target);
  bool process_all();
  void add_operation(CompilerOperation* operation); //potentially might be a bool but the general idea is that an operation should be vaild by default

  bool declare_variable(string name, int value);
  bool assign_to_variable(string name, int value);
  bool print_variable(string name) const;
  ~Compiler();
};
//TODO: eventually, those will need to be moved to a member class inside of Compiler itself. Not yet though
namespace asm_getters
{
  string create_variable(int value);
  string modify_variable(int value, int target_ptr, int stack_ptr);
  string print_variable(int target_ptr, int stack_ptr);
  string base_template();
  string end_program();
}
