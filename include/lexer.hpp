#pragma once
#include <string>
#include <vector>

using std::string;

//forward declaration
class Compiler;

enum class CharType
{
  Whitespace, //whitespace (anything that satisfies isspace(ch))
  Regular, //letters and underscore 
  Digit, //digits
  Operator, //characters 
  Singleton, //brackets etc, also semicolons 
  None, //default behavior, basically 'idk what this is'
};
namespace char_tests
{
  bool is_singleton(char ch); 
  bool is_operator(char ch);
  bool is_regular(char ch);
  bool is_digit(char ch);
}
CharType get_type(char ch);

std::vector<std::vector<string>> tokenize_file(string filename, Compiler& compiler); 
