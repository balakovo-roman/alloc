#include "logger.hpp"

#include <iostream>

#include "console_logger.hpp"

namespace logger
{

Logger& Logger::GetInstance()
{
    if (!instance_)
    {
        instance_ = MakeLogger();
    }

    return *instance_;
}

std::unique_ptr<Logger> Logger::MakeLogger()
{
    return std::make_unique<ConsoleLogger>(std::cout);
}

}  // namespace logger