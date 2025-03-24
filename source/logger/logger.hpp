#pragma once

#include <sstream>
#include <string>

namespace logger
{

class Logger
{
   public:
    virtual ~Logger() = default;

    template <typename... Args>
    void Log(Args&&... args)
    {
        std::ostringstream stream;
        
        ((stream << std::forward<Args>(args) << ' '), ...);
        
        std::string result = stream.str();
        
        if (!result.empty() && result.back() == ' ')
        {
            result.pop_back();
        }

        LogImpl(result);
    }

   private:
    virtual void LogImpl(const std::string& message) = 0;
};

}  // namespace logger
