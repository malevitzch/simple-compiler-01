#include <iostream>
using std::string;

namespace auxiliary
{
  bool valid_name_character(char ch);
  bool is_valid_starting_character(char ch);
  string trim_whitespace(string s);
}

//the function checks whether a variable name is valid (to avoid problems with keywords and the variables starting with numbers)
bool is_valid_variable_name(string variable_name);
bool is_a_number(string potential_number);
