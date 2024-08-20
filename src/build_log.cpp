#include <iostream>

#include "build_log.hpp"


void BuildLog::log_error(string text, int statement_index)
{
  errors.push_back("Error in statement " + std::to_string(statement_index) + ": " + text);
  error_count++;
}

void BuildLog::log_error(string text)
{
  errors.push_back("Error: " + text);
  error_count++;
}

void BuildLog::log_warning(string text, int statement_index)
{
  warnings.push_back("Warning in statement " + std::to_string(statement_index) + ": " + text);
  warning_count++;
}

void BuildLog::log_warning(string text)
{
  warnings.push_back("Warning: " + text);
  warning_count++;
}

void BuildLog::log_message(string text, int statement_index)
{
  messages.push_back("Message from statement " + std::to_string(statement_index) + ": " + text);
}

void BuildLog::log_message(string text)
{
  messages.push_back(text);
}

bool BuildLog::is_successful()
{
  return error_count == 0;
}

void BuildLog::dump(std::ostream& output_stream)
{
  //check if there are any errors
  if(!is_successful())
  {
    //in case of errors, output that compilation has halted and print all the errors
    output_stream << "Compilation halted due to the following " << error_count << " errors: \n";
    for(string& error : errors) output_stream<<error<<"\n";
  }
  else
  {
    output_stream << "Compilation finished with no errors and " + std::to_string(warning_count) + " warnings\n";
    if(warning_count > 0)
    {
      output_stream << "Warnings:\n";
      for(string& warning : warnings) output_stream << warning << "\n";
    }
    for(string& message : messages) output_stream << message << "\n";
  }
}
