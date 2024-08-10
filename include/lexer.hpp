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
  //checks whether the given character is a 'singleton', basically any character that can never be a part of a larger token
  bool is_singleton(char ch); 
  //checks if the character is an operator character
  bool is_operator(char ch);
  //checks if the character is regular, regular characters are letters and underscores
  bool is_regular(char ch);
  //check if the character is a digit
  bool is_digit(char ch);
}

//returns the type of the character given as an argument, if the type cannot be deduced CharType::None is returned
CharType get_type(char ch);

//splits the input file into tokens, grouped into statements
std::vector<std::vector<string>> tokenize_file(string filename, Compiler& compiler); 
