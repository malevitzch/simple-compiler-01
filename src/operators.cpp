#include "operators.hpp"

Operator::Operator(string name, string symbol, OperatorType type, int precedence) : name(name), symbol(symbol), type(type), precedence(precedence) {}
