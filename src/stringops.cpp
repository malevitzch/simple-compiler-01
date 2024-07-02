#include "../include/stringops.hpp"

namespace auxillary
{
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
