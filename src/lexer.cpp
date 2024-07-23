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

std::vector<std::vector<string>> tokenize_file(string filename)
{
  using namespace char_tests;
  Trie operator_trie(get_operator_symbols());
  std::vector<std::vector<string>> statements;
  std::fstream file_stream(filename);
  
  //Throw an exception in case the input file does not exist (This is preferred behavior, if user does not want the program to crash then they should check validity of filenames
  if(!file_stream.good())
  {
    throw std::ios_base::failure("File named \"" + filename + "\" does not exist");
  }

  //Prevent the file stream from skipping whitespace
  file_stream >> std::noskipws;

  //Declarations of variables
  CharType cur_type = CharType::None;
  char cur_char;
  CharType cur_char_type;
  string cur_token = "";
  std::vector<string> cur_statement = {};
  
  //Lambda that flushes the buffer and adds the token(s) to current statement
  auto finish_token = [&cur_type, &cur_token, &cur_statement, &operator_trie]()
  {
    //We do not add empty tokens, this is especially important in the case of something like ";;;"
    if(cur_token.empty()) return;

    //Operators are handled differently as they are initially bundles into a token together and then split using trie
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
  
  //Lambda that finishes the current statement and adds it to the statements vector
  auto finish_statement = [&finish_token, &statements, &cur_statement]()
  { 
    finish_token();
    if(cur_statement.empty()) return;
    statements.push_back(cur_statement);
    cur_statement.clear();
  };
  
  //loop runs until EOF
  while(!file_stream.eof())
  {
    //Get the next character from the file stream
    file_stream >> cur_char; 
    //Determine the type of the character
    cur_char_type = get_type(cur_char);
    //Proceed accordingly to the type
    switch(cur_char_type)
    {
      //Whitespace means that we need to end any token we currently have but is not added to a new token
      case CharType::Whitespace:
        finish_token();
        break;
      
      //Regular means keyword/varname
      case CharType::Regular:
        //if the current token is not a Regular token, we need to finish it before appending the character
        if(cur_type != CharType::Regular) finish_token();
        cur_type = CharType::Regular;
        cur_token += cur_char;
        break;

      //Digits can be either a number literal or part of a variable name (but cannot be the start of one)
      case CharType::Digit:
        //If current type is neither Digit nor Regular, then we need to finish the token and start a new token of Digit type which will be a number literal (since anything starting with a digit will be one)
        if(cur_type != CharType::Digit && cur_type != CharType::Regular)
        {
          finish_token();
          cur_type = CharType::Digit;
        }
        cur_token += cur_char;
        break;
        
      //Operators are handled the roughly same way Regular characters are aside from the way that finish_token works on them
      case CharType::Operator:
        if(cur_type != CharType::Operator) finish_token();
        cur_type = CharType::Operator;
        cur_token += cur_char;
        break;
      
      //Singleton characters such as brackets and semicolons instantly finish the current token
      case CharType::Singleton:
        finish_token();
        //If the character is a semicolon, we need to finish the current statement (but semicolon is not appended)
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
        string s = "";
        s += cur_char;
        throw std::runtime_error("Unknown character \"" + s + "\"\n");
        break;
    }
  }

  if(!cur_statement.empty())
  {
    //Handle syntax error. Basically last line has no semicolon
    //TODO: this should not be an exception, rather a build message that halts later compilation steps 
    throw std::runtime_error("No semicolon at the end of last statement");
  }

  return statements;
}
