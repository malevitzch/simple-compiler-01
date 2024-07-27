#pragma once
#include <string>
#include <vector>

#include "operators.hpp"

using std::string;

bool is_operator(string token);
void prefix_unary(std::vector<string>& expression);

std::vector<string> infix_to_postfix(std::vector<string> expression);

