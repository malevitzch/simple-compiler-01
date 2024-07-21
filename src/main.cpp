#include <iostream>
#include <fstream>
#include "compiler.hpp"
#include "lexer.hpp"

bool compile(string input_file, string output_file)
{
  //TODO: check if file exists
  std::vector<std::vector<std::string>> operations = tokenize_file(input_file);
  std::ofstream output(output_file);
  std::map<string, int> var_table;
  Compiler compiler(output);
  output << asm_getters::base_template();
  for(std::vector<string>& statement : operations)
  {
    compiler.add_operation(translate_statement(statement));
  }
  compiler.process_all();
  output << asm_getters::end_program();
  return true;
}
void lexer_test()
{
  std::vector<std::vector<string>> s = tokenize_file("debug_input");
  for(auto v : s)
  {
    for(string st : v)
    {
      std::cout<<st<<" ";
    }
      std::cout << " \n";
  }
}
int main()
{
  //lexer_test();
  string filename_in;
  std::cout<<"Please input the name of the input file: ";
  std::cin>>filename_in;
  string filename_out;
  std::cout<<"Please input the name of the output file: ";
  std::cin>>filename_out;
  compile(filename_in, filename_out);
}
