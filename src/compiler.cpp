#include <iostream>
#include "../include/compiler.hpp" 
#include "../include/parser.hpp"

bool Compiler::is_variable_registered(string name) const
{
  return variable_table.find(name) != variable_table.end();
}

bool Compiler::register_variable(string name, int value)
{
  if(is_variable_registered(name))
  {
    return false;
  }
  variable_table[name] = ++stack_ptr;
  return true;
}
bool Compiler::process_operation(CompilerOperation* operation)
{
  return operation->process(*this);
}

Compiler::Compiler(ostream& target) : target(target) {}

void Compiler::add_operation(CompilerOperation* operation)
{
  operations.push_back(operation);
}

bool Compiler::process_all() //potentially could return an optional information about which op fails
{
  std::cout << "Operation count is " << operations.size() << "\n";
  for(CompilerOperation* operation : operations)
  {
    if(!process_operation(operation)) return false;
  }
  return true;
}

bool Compiler::declare_variable(string name, int value)
{
  if(!register_variable(name, value)) return false; //return false as for failure in case of registration failure
  target << asm_getters::create_variable(value);
  return true;
}

bool Compiler::assign_to_variable(string name, int value)
{
  if(!is_variable_registered(name)) return false; //return false in case we try to access a variable that does not exist
  target << asm_getters::modify_variable(value, variable_table[name], stack_ptr);
  return true;
}
bool Compiler::print_variable(string name) const
{
  if(!is_variable_registered(name)) return false; //return false in case we try to print a nonexistent variable
  target << asm_getters::print_variable(variable_table.at(name), stack_ptr);
  return true;
}
Compiler::~Compiler()
{
  for(CompilerOperation* operation : operations)
  {
    delete operation;
  }
}

namespace asm_getters
{
  string create_variable(int value)
  {
    return "\tpush " + std::to_string(value) + "\n"; 
  }
  string modify_variable(int value, int target_ptr, int stack_ptr)
  {
    return "\tmov qword [rsp+" + std::to_string(8*(stack_ptr-target_ptr)) +"], " + std::to_string(value) + "\n";
  }
  string print_variable(int target_ptr, int stack_ptr)
  {
    return "\tpush qword [rsp+" + std::to_string(8*(stack_ptr-target_ptr)) + "]\n\tcall _print\n\tadd rsp, 8\n";
  }
  string base_template()
  {
    return "section .text\n\nextern _print\nglobal _start\n\n_start:\n";
  }
  string end_program()
  {
    return "\tmov rax, 60\n\tmov rdi, 1\n\tsyscall\n";
  }
}

