#include "build_log.hpp"
#include <string>

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
  //TODO: this doesn't sound right, do something about it
  messages.push_back("In statement: " + std::to_string(statement_index) + ": " + text);
}

void BuildLog::log_message(string text)
{
  messages.push_back(text);
}

bool BuildLog::is_successful()
{
  return error_count == 0;
}

//TODO: finish
void BuildLog::dump(std::ostream& output_stream)
{
  if(!is_successful())
  {
    output_stream << "Compilation halted due to the following errors: \n";
  }
}
