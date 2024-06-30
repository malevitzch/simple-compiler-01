#pragma once
#include <string>
class Compiler;
using std::string;
//all operations inherit from this class
class CompilerOperation
{
private:
public:
  CompilerOperation() = default;
  virtual bool process(Compiler& compiler);
};

class DeclarationOperation : public CompilerOperation
{
private:
  string variable_name;
  int value;
public:
  DeclarationOperation(string variable_name, int value);
  bool process(Compiler& compiler);
};

class AssignmentOperation : public CompilerOperation
{
private:
  AssignmentOperation() = delete;
  string variable_name;
  int value;
public:
  AssignmentOperation(string variable_name, int value);
  bool process(Compiler& compiler);
};

class PrintOperation : public CompilerOperation
{
private:
  PrintOperation() = delete;
  string variable_name;
public:
  PrintOperation(string variable_name);
  bool process(Compiler& compiler);
};
