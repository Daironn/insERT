#pragma once
#include <string>

namespace insERT
{
    enum class LogLevel
    {
        Info,
        Warning,
        Error
    };

    inline const char* LogLevelToString(LogLevel l)
    {
        switch (l)
        {
        case LogLevel::Info:
            return "INFO";
        case LogLevel::Warning:
            return "WARNING";
        case LogLevel::Error:
            return "ERROR";
        default:
            return "UNKNOWN";
        }
    }
} // namespace insERT

namespace insERT::logger
{
    struct ILogger
    {
        virtual ~ILogger() = default;
        virtual void Emit(insERT::LogLevel   level,
                          const std::string& timestamp,
                          const char*        file,
                          int                line,
                          const char*        func,
                          const std::string& message)
            = 0;
    };
} // namespace insERT::logger
