#include <iostream>
#include "compiler.hpp"
#include "lexer.hpp"
#include "shunting_yard.hpp"
int main()
{
  Compiler compiler;
  string filename_in;
  std::cout<<"Please input the name of the input file: ";
  std::cin>>filename_in;
  string filename_out;
  std::cout<<"Please input the name of the output file: ";
  std::cin>>filename_out;
  compiler.compile(filename_in, filename_out);
}
