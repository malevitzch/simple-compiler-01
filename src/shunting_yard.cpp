#include <algorithm>
#include <stack>
#include <stdexcept>

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
    //TODO: syntax is not being checked here, double binary operators might get prefixed which is not desired
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
  
  std::vector<string> postfix_expression;
  std::stack<string> operator_stack;

  //operator map contains operators already prefixed in case of unary oness
  std::map<string, Operator> operator_map = get_operator_map();

  for(string token : expression)
  {
    if(token == ")")
    {
      while(1)
      {
        if(operator_stack.empty())
        {
          throw std::runtime_error("Mismatched parentheses");
        }
        string cur = operator_stack.top();
        operator_stack.pop();
        if(cur == "(") break;
        else postfix_expression.push_back(cur);
      }
    }
    else if(operator_map.find(token) != operator_map.end())
    {

    }
    else
    {
      postfix_expression.push_back(token);
    }
  }

  return postfix_expression;
}
