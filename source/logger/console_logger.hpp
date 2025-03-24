#pragma once

#include "logger.hpp"

namespace logger
{

class ConsoleLogger final : public Logger
{
   public:
    explicit ConsoleLogger(std::ostream& outputStream);

    static ConsoleLogger& GetInstance();

    void LogImpl(const std::string& message) override;

   private:
    std::ostream& outputStream_;
};

#define LOG(...) logger::ConsoleLogger::GetInstance().Log(__VA_ARGS__)

}  // namespace logger