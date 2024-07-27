#pragma once
#include <string>
#include <vector>

using std::string;

//forward declaration
class Compiler;

//all operations inherit from this class
class CompilerOperation
{
private:
public:
  CompilerOperation() = default;
  virtual bool process(Compiler& compiler);
};

class InvalidOperation : public CompilerOperation
{
private:
  string error_message;
public:
  InvalidOperation(string error_message);
  bool process(Compiler& compiler) override;
};

class DeclarationOperation : public CompilerOperation
{
private:
  string variable_name;
  int value;
public:
  DeclarationOperation(string variable_name, int value);
  bool process(Compiler& compiler) override;
};

class AssignmentOperation : public CompilerOperation
{
private:
  AssignmentOperation() = delete;
  string variable_name;
  int value;
public:
  AssignmentOperation(string variable_name, int value);
  bool process(Compiler& compiler) override;
};

class PrintOperation : public CompilerOperation
{
private:
  PrintOperation() = delete;
  string variable_name;
public:
  PrintOperation(string variable_name);
  bool process(Compiler& compiler) override;
};

enum class Directive
{
  Declaration,
  Assignment,
  Print,
  NaD //Parsing error type
};
Directive get_operation(string opname);

CompilerOperation* translate_declaration(std::vector<string>& tokens);

CompilerOperation* translate_assignment(std::vector<string>& tokens);

CompilerOperation* translate_print(std::vector<string>& tokens);

CompilerOperation* translate_statement(std::vector<string> tokens);
