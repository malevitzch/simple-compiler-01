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
  std::ostream& diagnostic_stream = std::cout;
  int stack_ptr = 0;
  int cur_statement_index = 0;
  std::map<string, int> variables;
  std::vector<string> error_log;

  void log(string message);

  void register_variable(string name);
  
  [[nodiscard]]
  string push_stack(string name);
  [[nodiscard]]
  string declare(string name);
  [[nodiscard]]
  string dereference(string element, int index);
  [[nodiscard]]
  string base_template();
  [[nodiscard]]
  string end_program();

public:
  Compiler() = default;
  Compiler(std::ostream& diagnostic_stream);

  [[nodiscard]]
  string expression_eval(std::vector<string> expression);
  
  void compile(string input_filename, string output_filename);

  friend std::vector<std::vector<string>> tokenize_file(string filename, Compiler& compiler);
  friend std::vector<string> infix_to_postfix(std::vector<string> expression, Compiler& compiler);
};

