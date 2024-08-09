#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>

using std::string;

//TODO: Add functionality to change streams (pointer instead of reference but it's difficult to do due to deleted copy constructors)

class Compiler
{
private:
  //the diagnostic stream which the errors will be printed to in case of failure
  std::ostream& diagnostic_stream = std::cout;
  //pointer that helps keep track of current stack position for when we want to declare new variables
  int stack_ptr = 0;
  //diagnostic vairable that keeps track of current line for lexer and the compiler itself so that errors are more specific
  int cur_statement_index = 0;
  //the map that stores variables, could potentially be replaced with unordered_map
  std::map<string, int> variables;
  std::vector<string> error_log;
  
  //a function that adds an error to the log
  //NOTE: currently any error halts compilation completely
  //TODO: implement warnings, update the note (Also errors should be handled polymorphically)
  void log(string message);

  //a function that registers the variable of given name in the variable map
  //logs an error if variable is already registered
  void register_variable(string name);
  

  //the following functions are all assembly getters
  //the descriptions given describe what the assembly code given by them does, not what they do themselves
  //TODO: refactoring so that the names reflect that they generate assembly, maybe prefix them with asm or something like that
  
  //pushes the variable with the given name to the stack
  [[nodiscard]] string push_variable_to_stack(string name);

  //declares a variable on the stack, basically just reserves memory
  [[nodiscard]] string declare(string name);
  
  //dereferences the variable at the given position on the stack
  //the variable name is only used to check if a variable of such a name even exists
  //TODO: nonexistent deref can be caught earlier, not requiring a varname at this point and allowing for pointers in the future
  [[nodiscard]] string dereference(string variable_name, int index);
  
  //generates the boilerplate needed at the beginning of every program
  //TODO: separate the main function generator from this, add end_function and start_function
  [[nodiscard]] string base_template();
  
  //finishes the program
  //basically just mov rax, 60 mov rdi, 1 syscall
  [[nodiscard]] string end_program();

  //generates the assembly for evaluating an expression
  [[nodiscard]] string expression_eval(std::vector<string> expression);

public:
  //default constructor
  Compiler() = default;

  //special constructor in case you want a different diagnostic stream than cout which is the default
  Compiler(std::ostream& diagnostic_stream);

  //compiles the file with the name given by the first argument and saves the result in a file with the name given by the second argument
  void compile(string input_filename, string output_filename);

  //friend declarations for dependency injections
  friend std::vector<std::vector<string>> tokenize_file(string filename, Compiler& compiler);
  friend std::vector<string> infix_to_postfix(std::vector<string> expression, Compiler& compiler);
};

