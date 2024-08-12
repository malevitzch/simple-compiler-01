#pragma once
#include <string>
#include <vector>

#include "operators.hpp"

using std::string;
//forward declaration
class Compiler;

enum class TokenType
{
  Number,
  Variable,
  BinaryOperator,
  UnaryOperator,
  Unknown
};
//TODO: make a function which determines the type of a token


//function that checks whether or not the token is an operator
//NOTE: this is for non-prefixed operators
bool is_operator_noprefix(string token);

//prefixes all unary operators with "u" in the epxression
void prefix_unary(std::vector<string>& expression, Compiler& compiler);

//returns whether the expression has proper use operators
//basically a syntax check that allows 2 + 3 to go through but does not allow 2 3 +, both of which would get parsed to the same thing by the shunting yard algorithm later
bool is_valid_operator_placement(std::vector<string>& expression);


//converts an expression from infix notation to postfix notation
std::vector<string> infix_to_postfix(std::vector<string> expression, Compiler& compiler);

