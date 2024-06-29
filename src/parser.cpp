#include "../include/parser.hpp"

DeclarationOperation::DeclarationOperation(string variable_name, int value) : variable_name(variable_name),  value(value) {}
void DeclarationOperation::process(Compiler& compiler)
{
  compiler.declare_variable(variable_name, value);
}

AssignmentOperation::AssignmentOperation(string variable_name, int value) : variable_name(variable_name), value(value) {}
void AssignmentOperation::process(Compiler& compiler)
{
  compiler.assign_to_variable(variable_name, value);
}

PrintOperation::PrintOperation(string variable_name) : variable_name(variable_name) {}
void PrintOperation::process(Compiler& compiler)
{
  compiler.print_variable(variable_name);
}
