#include <string>

using std::string;

namespace auxiliary
{
  //checks whether the character is a valid name character (CharType::Regular or CharType::Digit)
  bool valid_name_character(char ch);
  //basically just CharType::Regular
  bool is_valid_starting_character(char ch);
  //removes whitespace from the end of s
  //NOTE: this is a dead function, there is no use for it
  string trim_whitespace(string s);
}

//the function checks whether a variable name is valid (to avoid problems with keywords and the variables starting with numbers)
bool is_valid_variable_name(string variable_name);
//checks whether the given string is a number
bool is_a_number(string potential_number);
