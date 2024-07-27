#include <algorithm>

#include "operators.hpp"
#include "shunting_yard.hpp"

bool is_operator(string token)
{
  std::vector<string> operators = get_operator_symbols();
  return std::find(operators.begin(), operators.end(), token) != operators.end();
}

void prefix_unary(std::vector<string>& expression)
{
  bool last_null_or_operator = true;
  for(string& token : expression)
  {
    //we ignore parentheses
    if(token == "(" || token == ")") continue;

    if(is_operator(token))
    {
      //an unary operator is either the first token of an expression or directly follows another operator (excluding brackets of course)
      if(last_null_or_operator) token = "u" + token;
      last_null_or_operator = true;
    }
    else
    {
      last_null_or_operator = false;
    }
  }
}

std::vector<string> infix_to_postfix(std::vector<string> expression)
{
  prefix_unary(expression);

  std::vector<string> posfix_expression;
  
  return posfix_expression;
}
