#pragma once

#include <memory>
#include <sstream>
#include <string>

namespace logger
{

class Logger
{
   public:
    virtual ~Logger() = default;

    static std::unique_ptr<Logger> MakeLogger();

    static Logger& GetInstance();

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

    static inline std::unique_ptr<Logger> instance_ = nullptr;
};

}  // namespace logger

#ifndef NDEBUG
#define LOG(...) logger::Logger::GetInstance().Log(__VA_ARGS__)
#else
#define LOG(...) ((void)0)
#endif