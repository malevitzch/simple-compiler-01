#include <iostream>
#include "compiler.hpp"

//all operations inherit from this abstract class so
class Operation
{
private:
public:
  Operation() = delete;
  virtual void process(Compiler& compiler) = 0;
};


