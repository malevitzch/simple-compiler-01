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
  //name of the operator, for example "Addition"
  string name;
  //de facto the default key of operator as stuff like "-" can be both unary and binary
  //NOTE: unary operators are instantiated with the prefixed symbols
  string symbol;
  //information on whether the operator is Unary or Binary
  OperatorType type;
  //lower number means the operator is processed earlier
  int precedence;
  //information on whether the operator is Left or Right associative
  Associativity associativity;
  //name of the assembly function that handles the operator
  string asm_call_name;
  //the only constructor you should explicitly be using
  Operator(string name, string symbol, OperatorType type, int precedence, Associativity associativity, string asm_call_name);
  //this one is only for convenience, there is no reason to create uninitialized operators but certain STL containers require a default constructor so I figured this could stay
  Operator() = default;
};

//function that initializes the opmap, only ever called by the get_operator_map function
static const std::map<string, Operator> _create_operator_map();
//function that returns a constant reference to the operator map
const std::map<string, Operator>& get_operator_map();
