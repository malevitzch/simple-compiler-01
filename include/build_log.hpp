#pragma once
#include <string>
#include <vector>
using std::string;

class BuildLog
{
private:
  int error_count = 0;
  int warning_count = 0;
  std::vector<string> errors;
  std::vector<string> warnings;
  std::vector<string> messages;
public:

  //logs an error in the statement with the given number
  void log_error(string text, int statement_index);

  //logs a global error 
  void log_error(string text);

  //logs a warning in the statement with the given number
  void log_warning(string text, int statement_index);

  //logs a global warning
  void log_warning(string text);

  //logs a message in the statement with the given number 
  //NOTE: this might actually be completely useless but I want it to exist for parity with log_error and log_message
  void log_message(string text, int statement_index);
  
  //logs a global compilation message
  void log_message(string text);

  //returns whether or not we have any errors
  [[nodiscard]] bool is_successful();

  //writes all the errors to on output stream 
  void dump(std::ostream& output_stream);
};
