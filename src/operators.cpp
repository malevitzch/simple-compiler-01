#include "operators.hpp"

const std::vector<string>& get_operator_symbols()
{
  static const std::vector<string> symbols = 
  {
    "+", "-", "*", "/", "=", "+=", "-=", "*=", "/=", "%", "%="
  };
  return symbols;
}

Operator::Operator(string name, string symbol, OperatorType type, int precedence, Associativity associativity, string asm_call_name) : name(name), symbol(symbol), type(type), precedence(precedence), associativity(associativity), asm_call_name(asm_call_name) {}


static const std::map<string, Operator> _create_operator_map()
{
  std::map<string, Operator> operator_map;
  //precedence is 3 for assignment, 1 for multiplication and division, 0 for unary, 2 for addition subtraction
  operator_map["="] = Operator("Assignment", "=", OperatorType::Binary, 3, Associativity::Right, "_operator_assignment");
  operator_map["+"] = Operator("Addition", "+", OperatorType::Binary, 2, Associativity::Left, "_operator_addition");
  operator_map["-"] = Operator("Subtraction", "-", OperatorType::Binary, 2, Associativity::Left, "_operator_subtraction");
  operator_map["*"] = Operator("Multiplication", "*", OperatorType::Binary, 1, Associativity::Left, "_operator_multiplication");
  operator_map["/"] = Operator("Division", "/", OperatorType::Binary, 1, Associativity::Left, "_operator_division");
  operator_map["%"] = Operator("Modulus", "%", OperatorType::Binary, 1, Associativity::Left, "_operator_modulus");
  operator_map["u-"] = Operator("Negation", "-", OperatorType::Unary, 0, Associativity::Right, "_operator_negation");
  return operator_map;
}

const std::map<string, Operator>& get_operator_map()
{
  static const std::map<string, Operator>& operator_map = _create_operator_map();
  return operator_map;
}
