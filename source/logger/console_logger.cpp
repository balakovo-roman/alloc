#include "console_logger.hpp"

#include <iostream>

namespace logger
{

ConsoleLogger::ConsoleLogger(std::ostream& outputStream)
    : outputStream_(outputStream)
{
}
void ConsoleLogger::LogImpl(const std::string& message)
{
    outputStream_ << message << std::endl;
}

}  // namespace logger