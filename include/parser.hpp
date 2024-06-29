#pragma once
#include <string>
class Compiler;
using std::string;
//all operations inherit from this class
class CompilerOperation
{
private:
protected:
  
public:
  CompilerOperation() = default;
  virtual void process(Compiler& compiler);
};

class DeclarationOperation : public CompilerOperation
{
private:
  string variable_name;
  int value;
public:
  DeclarationOperation(string variable_name, int value);
  void process(Compiler& compiler);
};

class AssignmentOperation : public CompilerOperation
{
private:
  AssignmentOperation() = delete;
  string variable_name;
  int value;
public:
  AssignmentOperation(string variable_name, int value);
  void process(Compiler& compiler);
};

class PrintOperation : public CompilerOperation
{
private:
  PrintOperation() = delete;
  string variable_name;
public:
  PrintOperation(string variable_name);
  void process(Compiler& compiler);
};
