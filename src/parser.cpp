#include "parser.hpp"
#include "compiler.hpp"
#include "stringops.hpp"
bool CompilerOperation::process(Compiler& compiler) {std::cout<<"Error: operation without type\n"; return true;}

DeclarationOperation::DeclarationOperation(string variable_name, int value) : variable_name(variable_name),  value(value) {}
bool DeclarationOperation::process(Compiler& compiler)
{
  std::cout << "DECLARED " << variable_name << "\n";
  return compiler.declare_variable(variable_name, value);
}

InvalidOperation::InvalidOperation(string error_message) : error_message(error_message) {}
bool InvalidOperation::process(Compiler& compiler) 
{
  std::cout << "INVALID OPERATION, ERROR MESSAGE: " << error_message << "\n";
  return false;
}


AssignmentOperation::AssignmentOperation(string variable_name, int value) : variable_name(variable_name), value(value) {}
bool AssignmentOperation::process(Compiler& compiler)
{
  std::cout << "SET VALUE OF " << variable_name << " TO " <<value << "\n";
  return compiler.assign_to_variable(variable_name, value);
}

PrintOperation::PrintOperation(string variable_name) : variable_name(variable_name) {}
bool PrintOperation::process(Compiler& compiler)
{
  std::cout << "PRINTED " << variable_name << "\n";
  return compiler.print_variable(variable_name);
}

Directive get_operation(string opname)
{
  if(opname == "DECL") return Directive::Declaration;
  if(opname == "ASSIGN") return Directive::Assignment;
  if(opname == "PRINT") return Directive::Print;
  return Directive::NaD;
}

CompilerOperation* translate_declaration(std::vector<string>& tokens)
{
  if(tokens.size() < 2) return new InvalidOperation("Attempting to declare a variable without a name");
  if(!is_valid_variable_name(tokens[1])) return new InvalidOperation("Attempting to declare a variable of name: " + tokens[1] + " which is not a valid variable name");
  //TODO: Add the aseembly_getter for value-less declarations
  if(tokens.size() == 2) return new InvalidOperation("Declarations without value are not yet supported");
  //Expressions would be parsed here, for now we use a heuristic for detecting '-'
  if(tokens[2] == "-")
  {
    if(tokens.size() == 4)
    {
      if(!is_a_number(tokens[3])) return new InvalidOperation("Invalid number literal: -" + tokens[3]);
      return new DeclarationOperation(tokens[1], stoi("-" + tokens[3])); //stoi is kinda dangerous
    }
    else
    {
      return new InvalidOperation("Too many tokens");
    }
  }
  if(!is_a_number(tokens[2])) return new InvalidOperation("Invalid number literal: " + tokens[2]);
  return new DeclarationOperation(tokens[1], stoi(tokens[2])); //stoi is kinda dangerous
}

CompilerOperation* translate_assignment(std::vector<string>& tokens)
{
  if(tokens.size() < 2) return new InvalidOperation("Attempting to assign to a variable without a name");
  if(!is_valid_variable_name(tokens[1])) return new InvalidOperation("Attempting to assign to an invalid variable of name: " + tokens[1] + " which is not a valid variable name");
  if(tokens.size() == 2) return new InvalidOperation("Attempting to assign without a value");
  //Expressions would be parsed here, for now we use a heuristic for detecting '-'
  if(tokens[2] == "-")
  {
    if(tokens.size() == 4)
    {
      if(!is_a_number(tokens[3])) return new InvalidOperation("Invalid number literal: -" + tokens[3]);
      return new AssignmentOperation(tokens[1], stoi("-" + tokens[3])); //stoi is kinda dangerous
    }
    else
    {
      return new InvalidOperation("Too many tokens");
    }
  }
  if(!is_a_number(tokens[2])) return new InvalidOperation("Invalid number literal: " + tokens[2]);
  return new DeclarationOperation(tokens[1], stoi(tokens[2])); //stoi is kinda dangerous
}

CompilerOperation* translate_print(std::vector<string>& tokens)
{
  if(tokens.size() < 2) return new CompilerOperation();
  if(!is_valid_variable_name(tokens[1])) return new InvalidOperation("Attempting to print variable of name: " + tokens[1] + " which is not a valid variable name");
  return new PrintOperation(tokens[1]);
}

CompilerOperation* translate_statement(std::vector<string> tokens)
{
  if(tokens.size() < 1) return new InvalidOperation("Empty statement error (this is the compiler's fault, not yours)");
  Directive optype = get_operation(tokens[0]);
  switch(optype)
  {
    case Directive::Declaration:
      return translate_declaration(tokens);
    case Directive::Assignment:
      return translate_assignment(tokens);
    case Directive::Print:
      return translate_print(tokens);
    default:
      return new InvalidOperation("Invalid directive: " + tokens[0]);
      break;
  }
}
