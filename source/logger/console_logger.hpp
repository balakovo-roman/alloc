#pragma once

#include "logger.hpp"

namespace logger
{

class ConsoleLogger final : public Logger
{
   public:
    explicit ConsoleLogger(std::ostream& outputStream);

    void LogImpl(const std::string& message) override;

   private:
    std::ostream& outputStream_;
};

}  // namespace logger