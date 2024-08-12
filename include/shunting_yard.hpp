#pragma once
#include <string>
#include <vector>

#include "operators.hpp"

using std::string;
//forward declaration
class Compiler;

//function that checks whether or not the token is an operator
//NOTE: this is for non-prefixed operators
bool is_operator_noprefix(string token);

//prefixes all unary operators with "u" in the epxression
void prefix_unary(std::vector<string>& expression, Compiler& compiler);

//converts an expression from infix notation to postfix notation
std::vector<string> infix_to_postfix(std::vector<string> expression, Compiler& compiler);

