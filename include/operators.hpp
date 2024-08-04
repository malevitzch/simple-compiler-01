#pragma once
#include <string>
#include <vector>
#include <map>

using std::string;

const std::vector<string>& get_operator_symbols();

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
  string asm_call_name;
  Operator(string name, string symbol, OperatorType type, int precedence, Associativity associativity, string asm_call_name);
  Operator() = default;
};

std::map<string, Operator> get_operator_map();
