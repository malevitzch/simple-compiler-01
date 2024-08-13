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
  Bracket,
  BinaryOperator,
  UnaryOperator,
  Unknown
};

//TODO: make a function which determines the type of a token
namespace token_tests
{
  //a number is a string consisting only of digits between 0 and 9
  bool is_number(string& token);
  //a variable starts with an underscore or a letter, any later character may be a number, letter, or an underscore
  bool is_variable(string& token);
  //uses the operator map to determine 
  bool is_binary_operator(string& token);
  //uses the operator map to determine
  bool is_unary_operator(string& token);
  //currently token == "(" || token == ")"
  bool is_bracket(string& token);
}

TokenType get_token_type(string& token);

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

