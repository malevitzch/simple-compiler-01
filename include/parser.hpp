#pragma once
#include "compiler.hpp"

//all operations inherit from this abstract class so
class Operation
{
private:
protected:
  Operation();
public:
  virtual void process(Compiler& compiler) = 0;
};

class DeclarationOperation : public Operation
{
private:
  DeclarationOperation() = delete;
  string variable_name;
  int value;
public:
  DeclarationOperation(string variable_name, int value);
  void process(Compiler& compiler);
};

class AssignmentOperation : public Operation
{
private:
  AssignmentOperation() = delete;
  string variable_name;
  int value;
public:
  AssignmentOperation(string variable_name, int value);
  void process(Compiler& compiler);
};

class PrintOperation : public Operation
{
private:
  PrintOperation() = delete;
  string variable_name;
public:
  PrintOperation(string variable_name);
  void process(Compiler& compiler);
};
