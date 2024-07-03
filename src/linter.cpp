#include "../include/linter.hpp"
#include <set>
//This assumes the file exists. Todo: add error handling. I'm thinking variant or optional return type?

bool is_singleton(char ch)
{
  std::set<char> singletons = 
  {
    '(', ')', '{', '}', '[', ']', '?', '!', 
  };
  return singletons.find(ch) != singletons.end();
}
bool is_operator(char ch)
{
  std::set<char> operators = 
  {
    '+', '-', '*', '/', '>', '<', '=', '#'
  };
  return operators.find(ch) != operators.end();
}
std::vector<std::vector<string>> tokenize_file(string filename)
{
  std::vector<std::vector<string>> tokenized_file;
  std::fstream file_stream(filename);
  
  file_stream >> std::noskipws;
  bool finished = false;
  CharType cur_type = CharType::None;
  char cur_char;
  string cur_token = "";
  std::vector<string> cur_statement = {};
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
    if(cur_char == ';')
    {
      if(!cur_token.empty())
      {
        cur_statement.push_back(cur_token);
        cur_token = "";
      }
      if(!cur_statement.empty())
      {
        tokenized_file.push_back(cur_statement);
        cur_statement = {};
      }
      cur_type = CharType::None;
    }
    else if(isspace(cur_char))
    {
      if(!cur_token.empty())
      {
        cur_statement.push_back(cur_token);
        cur_token = "";
      }
      cur_type = CharType::None;
    }
    else
    {
      if(is_singleton(cur_char))
      {
        if(!cur_token.empty())
        {
          cur_statement.push_back(cur_token);
          cur_token = "";
        }
        string temp = "";
        temp += cur_char;
        cur_statement.push_back(temp);
        cur_type = CharType::None;
      }
      else if(is_operator(cur_char))
      {
        if(cur_type != CharType::Operator && cur_type != CharType::None)
        {
          if(!cur_token.empty())
          {
            cur_statement.push_back(cur_token);
            cur_token = "";
          }
        }
      cur_token += cur_char;
      cur_type = CharType::Operator;
      }
      else
      {
        //TODO: Add check for character being 'Unknown' 
        if(cur_type != CharType::Regular && cur_type != CharType::None)
        {
          if(!cur_token.empty())
          {
            cur_statement.push_back(cur_token);
            cur_token = "";
          } 
        }
        cur_token += cur_char;
      }
    }
  }
  return tokenized_file;
}
