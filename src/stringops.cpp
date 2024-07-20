#include "stringops.hpp"
#include <algorithm>
namespace auxiliary
{
  bool valid_name_character(char ch)
  {
    return (ch == '_') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9');
  }
  bool is_valid_starting_character(char ch)
  {
    return (ch == '_') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
  }
  string trim_whitespace(string s)
  {
    if(s.size() == 0) return s; //safety check for empty string
    int l = 0;
    int r = s.size()-1;
    while(l <= r)
    {
      if(isspace(s[l]))
      {
         l++;
      }
      else if(isspace(s[r]))
      {
         r--;
      }
      else
      {
         break;
      }
    }
    if(l > r)
    {
      return "";
    }
    return s.substr(l, r - l + 1);
  }
}

bool is_valid_variable_name(string variable_name)
{
  using namespace auxiliary;
  if(variable_name.size() == 0) return false; //check for empty name
  if(!is_valid_starting_character(variable_name[0])) return false; //invalid starting character - for example starting with numbers is illegal 
  
  return all_of(variable_name.begin(), variable_name.end(), 
    [](char ch)
    {
      return valid_name_character(ch);
    });
}

bool is_a_number(string potential_number)
{
  return std::all_of(potential_number.begin(), potential_number.end(),
     [](char ch)
     {
        return ch >= '0' && ch <= '9';
     });
}
