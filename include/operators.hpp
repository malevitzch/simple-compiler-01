#pragma once
#include <string>
#include <vector>
#include <map>

using std::string;

//returns a constant reference ot the vector of operator symbols
//NOTE: those are symbols before marking unary ones
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

//function that initializes the opmap, only ever called by the get_operator_map function
static const std::map<string, Operator> _create_operator_map();
const std::map<string, Operator>& get_operator_map();
