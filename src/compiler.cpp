#include <stack>
#include <cassert>
#include <fstream>
#include <sstream>

#include "compiler.hpp"
#include "operators.hpp"
#include "shunting_yard.hpp"
#include "stringops.hpp"
#include "lexer.hpp"

void Compiler::log(string message)
{
  error_log.push_back("In statement " + std::to_string(cur_statement_index) + ": " + message);
}

void Compiler::register_variable(string name)
{
  //check if variable is not already registered
  if(variables.find(name) != variables.end())
  {
    log("Variable \"" + name + "\" is already registered");
  }
  variables[name] = ++stack_ptr;
}

string Compiler::declare(string name)
{
  register_variable(name);
  return "\tsub rsp, 8\n";
}

string Compiler::dereference(string element, int index)
{
  if(variables.find(element) == variables.end()) {} //error
  return "\tmov rax, [rsp+" + std::to_string(index * 8) +"]\n\tmov rax, [rax]\n\tmov [rsp+" + std::to_string(index * 8) + "], rax\n";
}

string Compiler::base_template()
{
  //TODO: separate function start template from main template for when we want to implement functions
  string base_temp = "section .text\n\nextern _print\n";
  for(auto&[key, op] : get_operator_map())
  {
    base_temp += "extern " + op.asm_call_name + "\n";
  }
  base_temp += "global _start\n\n_start:\n\tpush rbp\n\tmov rbp, rsp\n";
  return base_temp;
}

string Compiler::end_program()
{
  return "\tmov rax, 60\n\tmov rdi, 1\n\tsyscall\n";
}

Compiler::Compiler(std::ostream& diagnostic_stream) : diagnostic_stream(diagnostic_stream) {}

string Compiler::expression_eval(std::vector<string> expression)
{
  const std::map<string, Operator>& operator_map = get_operator_map();
  std::vector<string> postfix_expr = infix_to_postfix(expression, *this);
  string result = "";
  std::stack<string> value_stack;
  for(string token : postfix_expr)
  {
    if(is_a_number(token))
    {
      value_stack.push("#");
      result += "\tpush " + token + "\n";
    }
    else if(is_valid_variable_name(token))
    {
      if(variables.find(token) == variables.end())
      {
        log("Invalid token \"" + token + "\""); 
      }
      value_stack.push(token);
      result += "\tmov rax, rbp\n\tsub rax, " + std::to_string(8*variables[token]) + "\n\tpush rax\n";
    }
    else
    {
      if(operator_map.find(token) == operator_map.end())
      {
        log("Invalid token \"" + token + "\"");
      }
      Operator op = operator_map.at(token);
      if(op.type == OperatorType::Unary)
      {
        if(value_stack.size() < 1) 
        {
          log("Not enough operands for unary operator");
          return "";
        }
        string op1 = value_stack.top();
        value_stack.pop();

        result += "\tcall " + op.asm_call_name + "\n";

        value_stack.push("#");
      }
      else
      {
        //handle situation where there are not enough operands on the stack
        if(value_stack.size() < 2) 
        {
          log("Not enough operands for binary operator");
          return "";
        }
        string op2 = value_stack.top();
        value_stack.pop();
        string op1 = value_stack.top();
        value_stack.pop();
        //TODO: come up with a much better way of processing derefs for operators, perhaps some sort of lambda that classifies the needs to deref?
        if(op.symbol == "=")
        {
          if(op1 == "#")
          {
            log("Cannot assign to an rvalue");
            return "";
          }
          if(op2 != "#") result += dereference(op2, 1);
        }
        else
        {
          if(op1 != "#") result += dereference(op1, 1);
          if(op2 != "#") result += dereference(op2, 0);
        }

        result += "\tcall " + op.asm_call_name + "\n";
        
        value_stack.push("#");

      }
    }
  }
  if(value_stack.size() != 1)
  {
    log("Expression does not evaluate to a single value");
    return "";
  }
  return result;
}

void Compiler::compile(string input_filename, string output_filename)
{
  std::vector<std::vector<string>> statements = tokenize_file(input_filename, *this);

  if(!error_log.empty())
  {
    diagnostic_stream << "Tokenization failed due to the following errors:\n";
    for(string& error : error_log) diagnostic_stream<<error<<"\n";
    return;
  }

  std::stringstream buffer;
  buffer << base_template();
  for(std::vector<string>& statement : statements)
  {
    cur_statement_index++;
    if(statement.size() == 0) continue;
    if(statement[0] == "decl")
    {
      if(statement.size() < 2)
      {
        log("expected variable name after 'decl'");
      }
      if(!is_valid_variable_name(statement[1]))
      {
        log("Invalid variable name: \"" + statement[1] + "\"");
      }
      buffer << declare(statement[1]);
      if(statement.size() > 2)
      {
        std::vector<string> expr(statement.begin()+1, statement.end());
        buffer << expression_eval(expr);
      }
    }
    else if(statement[0] == "print")
    {
      //TODO: make print use expression eval
      if(statement.size() < 2)
      {
        log("expected variable name after 'decl'");
      }
      if(!is_valid_variable_name(statement[1]))
      {
        log("invalid variable name \"" + statement[1] + "\"");
      }
      buffer << "\tpush qword [rbp-" + std::to_string(8*variables[statement[1]]) + "]\n\tcall _print\n\tadd rsp, 8\n";
    }
    else
    {
      buffer << expression_eval(statement);
    }
  }
  buffer << end_program();
  if(error_log.empty())
  {
    std::ofstream output(output_filename);
    output << buffer.str();
    diagnostic_stream << "Compilation successful, the contents have been written to \"" + output_filename + "\"\n"; 
  }
  else
  {
    //TODO: make this use a diagnostic output ostream as a parameter for the compiler (basically you can instantiate compiler with any ostream you want and everything gets written there)
    diagnostic_stream << "Compilation failed due to the following errors:\n";
    for(string& error : error_log) diagnostic_stream << error<<"\n";
  }
}
