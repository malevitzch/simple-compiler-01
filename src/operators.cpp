#include "operators.hpp"

Operator::Operator(string name, string symbol, OperatorType type, int precedence, Associativity associativity) : name(name), symbol(symbol), type(type), precedence(precedence), associativity(associativity) {}
std::vector<string> get_operator_symbols()
{
  return 
  {
    "+", "-", "*", "/", "!", "=", "+=", "-=", "*=", "/="
  };
}

