#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using std::string;

enum class CharType
{
  None,
  Regular,
  Operator,
  Singleton
};

bool is_singleton(char ch);
std::vector<std::vector<string>> tokenize_file(string filename); 
