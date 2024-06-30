#include "../include/parser.hpp"
#include "../include/compiler.hpp"
bool CompilerOperation::process(Compiler& compiler) {std::cout<<"Error: operation without type\n"; return true;}

DeclarationOperation::DeclarationOperation(string variable_name, int value) : variable_name(variable_name),  value(value) {}
bool DeclarationOperation::process(Compiler& compiler)
{
  std::cout<< "DECLARED" << variable_name << "\n";
  return compiler.declare_variable(variable_name, value);
}

AssignmentOperation::AssignmentOperation(string variable_name, int value) : variable_name(variable_name), value(value) {}
bool AssignmentOperation::process(Compiler& compiler)
{
  return compiler.assign_to_variable(variable_name, value);
}

PrintOperation::PrintOperation(string variable_name) : variable_name(variable_name) {}
bool PrintOperation::process(Compiler& compiler)
{
  return compiler.print_variable(variable_name);
}
