#pragma once
#include <string>
using std::string;
enum class OperatorType
{
  Unary,
  Binary
};
enum class Associativity
{
  Left, 
  Right
};
struct Operator
{
  string name; //de facto the default key of operator as stuff like "-" can be both unary and binary
  string symbol;
  OperatorType type;
  int precedence;
  Associativity associativity;
  Operator(string name, string symbol, OperatorType type, int precedence, Associativity associativity);
};
