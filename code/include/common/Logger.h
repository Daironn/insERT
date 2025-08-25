#pragma once
#include <chrono>
#include <ctime>
#include <format>
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>

namespace insERT::logger
{
    enum class LogLevel
    {
        Info,
        Warning,
        Error
    };

    class Logger
    {
      public:
        template <typename... Args>
        static void Log(LogLevel         level,
                        const char*      file,
                        int              line,
                        const char*      func,
                        std::string_view fmt,
                        Args&&... args)
        {
            std::string levelStr;
            switch (level)
            {
            case LogLevel::Info:
                levelStr = "INFO";
                break;
            case LogLevel::Warning:
                levelStr = "WARNING";
                break;
            case LogLevel::Error:
                levelStr = "ERROR";
                break;
            }

            auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::string message = std::vformat(fmt, std::make_format_args(args...));

            std::tm tm_buf;
            localtime_s(&tm_buf, &time);
            std::cout << "[" << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S") << "] " << levelStr
                      << " " << file << ":" << line << " (" << func << "): " << message
                      << std::endl;
        }
    };

#define LOG_INFO(fmt, ...)                                                                         \
    Logger::Log(logger::LogLevel::Info, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...)                                                                      \
    Logger::Log(logger::LogLevel::Warning, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)                                                                        \
    Logger::Log(logger::LogLevel::Error, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

} // namespace insERT::logger
