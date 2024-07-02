#include "../include/linter.hpp"

//This assumes the file exists. Todo: add error handling. I'm thinking variant or optional return type?
std::vector<std::vector<string>> tokenize_file(string filename)
{
  std::vector<std::vector<string>> tokenized_file;
  std::fstream file_stream(filename);
  
  file_stream >> std::noskipws;
  bool finished = false;
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
    }
    else if(isspace(cur_char))
    {
      if(!cur_token.empty())
      {
        cur_statement.push_back(cur_token);
        cur_token = "";
      }

    }
    else
    {
      cur_token += cur_char;
    }
  }
  return tokenized_file;
}
