#include "lexer.hpp"
#include "operator_trie.hpp"
#include <iostream>
#include <fstream>
#include <set>
namespace char_tests
{
  bool is_singleton(char ch)
  {
    std::set<char> singletons = 
    {
      '(', ')', '{', '}', '[', ']', '?', ';', 
    };
    return singletons.find(ch) != singletons.end();
  }
  bool is_operator(char ch)
  {
    std::set<char> operators = 
    {
      '+', '-', '*', '/', '>', '<', '=', '!'
    };
    return operators.find(ch) != operators.end();
  }
  bool is_regular(char ch)
  {
    return (ch == '_') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
  }
  bool is_digit(char ch)
  {
    return ch >= '0' && ch <= '9';
  }
}
CharType get_type(char ch)
{
  using namespace char_tests;
  if(isspace(ch)) return CharType::Whitespace;
  if(is_regular(ch)) return CharType::Regular;
  if(is_digit(ch)) return CharType::Digit;
  if(is_operator(ch)) return CharType::Operator;
  if(is_singleton(ch)) return CharType::Singleton;
  return CharType::None;
}

std::vector<string> get_operator_symbols()
{
  return 
  {
    "+", "-", "*", "/", "!", "=", "+=", "-=", "*=", "/="
  };
}

//This assumes the file exists. Todo: add error handling. I'm thinking variant or optional return type? NVM, probably exceptions
std::vector<std::vector<string>> tokenize_file(string filename)
{
  using namespace char_tests;
  Trie operator_trie(get_operator_symbols());
  std::vector<std::vector<string>> statements;
  std::fstream file_stream(filename);
  file_stream >> std::noskipws;
  CharType cur_type = CharType::None;
  char cur_char;
  CharType cur_char_type;
  string cur_token = "";
  std::vector<string> cur_statement = {};

  auto finish_token = [&cur_type, &cur_token, &cur_statement, &operator_trie]()
  {
    if(cur_token.empty()) return;
    if(cur_type == CharType::Operator)
    {
      std::vector<string> split = operator_trie.split_string(cur_token);
      for(string& s : split) cur_statement.push_back(s);
    }
    else
    {
      cur_statement.push_back(cur_token);
    }
    cur_token = "";
    cur_type = CharType::None;
  };

  auto finish_statement = [&finish_token, &statements, &cur_statement]()
  { 
    finish_token();
    if(cur_statement.empty()) return;
    statements.push_back(cur_statement);
    cur_statement.clear();
  };

  while(true)
  {
    if(file_stream.eof()) 
    {
      if(!cur_statement.empty())
      {
        //handle code error. Basically last line has no semicolon
      }
      break;
    }
    file_stream >> cur_char; 
    cur_char_type = get_type(cur_char);
    switch(cur_char_type)
    {

      case CharType::Whitespace:
        finish_token();
        break;

      case CharType::Regular:
        if(cur_type != CharType::Regular) finish_token();
        cur_type = CharType::Regular;
        cur_token += cur_char;
        break;

      case CharType::Digit:
        if(cur_type != CharType::Digit && cur_type != CharType::Regular)
        {
          finish_token();
          cur_type = CharType::Digit;
        }
        cur_token += cur_char;
        break;

      case CharType::Operator:
        if(cur_type != CharType::Operator) finish_token();
        cur_type = CharType::Operator;
        cur_token += cur_char;
        break;

      case CharType::Singleton:
        finish_token();
        if(cur_char == ';')
        {
          finish_statement();
        }
        else
        {
          cur_token += cur_char;
          finish_token();
        }
        break;

      default:
        //handle unknown character here
        break;
    }
  }

  if(!cur_statement.empty())
  {
    //handle lack of closing ; here
  }
  return statements;
}
