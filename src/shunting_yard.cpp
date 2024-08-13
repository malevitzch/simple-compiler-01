#include <algorithm>
#include <stack>
#include <cassert>

#include "operators.hpp"
#include "shunting_yard.hpp"
#include "compiler.hpp"

namespace token_tests
{

  bool is_number(string& token)
  {
    //we assume there are no empty tokens, and if there were, we wouldn't want to classify them as numbers
    assert(token.size() > 0);
    return std::all_of(token.begin(), token.end(), [](char ch){return ch >= '0' && ch <= '9';});
  }
  
  bool is_variable(string& token)
  {
    //the token should always contain at least one character, else the program crashes
    //empty tokens would mean a mistake in the lexer code
    assert(token.size() > 0);
    return std::all_of(token.begin()+1, token.end(), [](char ch)
    {
      return ch == '_' || ch >= '0' && ch <= '9' || ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
    });
  }

  bool is_binary_operator(string& token)
  {
    std::map<string, Operator> operator_map = get_operator_map();
    return operator_map.find(token) != operator_map.end() && operator_map.at(token).type == OperatorType::Binary;
  }

  bool is_unary_operator(string& token)
  {
    std::map<string, Operator> operator_map = get_operator_map();
    return operator_map.find(token) != operator_map.end() && operator_map.at(token).type == OperatorType::Unary;
  }
  
  bool is_bracket(string& token)
  {
    return token == "(" || token == ")";
  }

}

TokenType get_token_type(string& token)
{
  using namespace token_tests;
  if(is_number(token)) return TokenType::Number;
  if(is_variable(token)) return TokenType::Variable;
  if(is_binary_operator(token)) return TokenType::BinaryOperator;
  if(is_unary_operator(token)) return TokenType::UnaryOperator;
  if(is_bracket(token)) return TokenType::Bracket;
  return TokenType::Unknown;
}

bool is_operator_noprefix(string token)
{
  const std::vector<string>& operators = get_operator_symbols();
  return std::find(operators.begin(), operators.end(), token) != operators.end();
}

void prefix_unary(std::vector<string>& expression, Compiler& compiler)
{
  bool last_null_or_operator = true;
  std::map<string, Operator>operator_map = get_operator_map();
  for(string& token : expression)
  {
    //we ignore parentheses
    if(token == "(" || token == ")") continue;
    if(is_operator_noprefix(token)) 
    {
      //an unary operator is either the first token of an expression or directly follows another operator (excluding brackets of course)
      if(last_null_or_operator) 
      {
        if(operator_map.find("u" + token) == operator_map.end())
        {
          compiler.log("Operator \"" + token + "\" is being interpreted as unary operator but no such unary operator exists");
          return;
        }
        token = "u" + token;
      }
      last_null_or_operator = true;
    }
    else
    {
      last_null_or_operator = false;
    }
  }
}

//TODO: finish the function
bool is_valid_operator_placement(std::vector<string>& expression)
{
  std::vector<string> filtered;
  //parentheses are completely ignored as they are checked by the shunting yard algorithm
  //we filter out parentheses
  for(string& token : expression)
  {
    if(token != "(" && token != ")") filtered.push_back(token);
  }
  return true;
}

std::vector<string> infix_to_postfix(std::vector<string> expression, Compiler& compiler)
{
  prefix_unary(expression, compiler);
  
  //TODO: validate here using a special function

  std::vector<string> postfix_expression;
  std::stack<string> operator_stack;

  //operator map contains operators already prefixed in case of unary oness
  const std::map<string, Operator>& operator_map = get_operator_map();

  for(string token : expression)
  {
    if(token == ")")
    {
      while(true)
      {
        if(operator_stack.empty())
        {
          compiler.log("Mismatched parentheses");
        }
        string cur = operator_stack.top();
        operator_stack.pop();
        if(cur == "(") break;
        else postfix_expression.push_back(cur);
      }
    }
    else if(operator_map.find(token) != operator_map.end())
    {
      while(!operator_stack.empty() && operator_stack.top() != "(")
      {
        Operator o1 = operator_map.at(token);
        Operator o2 = operator_map.at(operator_stack.top());
        if(o2.precedence < o1.precedence || (o1.precedence == o2.precedence && o1.associativity == Associativity::Left))
        {
          postfix_expression.push_back(operator_stack.top());
          operator_stack.pop();
        }
        else break;
      }
      operator_stack.push(token);
    }
    else if(token == "(") operator_stack.push(token);
    else postfix_expression.push_back(token);
  }
  while(!operator_stack.empty())
  {
    if(operator_stack.top() == "(") compiler.log("Mismatched parentheses");
    postfix_expression.push_back(operator_stack.top());
    operator_stack.pop();
  }
  return postfix_expression;
}
