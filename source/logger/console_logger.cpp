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

ConsoleLogger& ConsoleLogger::GetInstance()
{
    static ConsoleLogger instance{std::cout};
    return instance;
}

}  // namespace logger