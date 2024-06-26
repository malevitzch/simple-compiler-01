#include <iostream>
#include "../include/compiler.hpp"

int main()
{
  std::cout<<asm_getters::register_variable(15);
  std::cout<<asm_getters::register_variable(18);
  std::cout<<asm_getters::register_variable(12);
  std::cout<<asm_getters::modify_variable(7, 1, 2);
}
