#pragma once
#include <string>
#include <vector>
#include <map>

using std::string;

class Compiler
{
private:
  int stack_ptr = 0;
  int cur_statement_index = 0;
  std::map<string, int> variables;
  std::vector<string> error_log;

  void log(string message);

  void register_variable(string name);

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
  [[nodiscard]]
  string expression_eval(std::vector<string> expression);
  void compile(string input_filename, string output_filename);
};

