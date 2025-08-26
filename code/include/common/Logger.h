#pragma once

#include <chrono>
#include <ctime>
#include <exception>
#include <format>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <string_view>
#include <utility>

#include "ConsoleLogger.h"
#include "FileLogger.h"
#include "ILogger.h"

namespace insERT::logger
{

    class Logger
    {
      public:
        static void SetBackend(std::shared_ptr<ILogger> backend)
        {
            std::scoped_lock lock(GetMutex());
            GetInstance() = std::move(backend);
        }

        static std::shared_ptr<ILogger> GetBackend()
        {
            std::scoped_lock lock(GetMutex());
            return GetInstance();
        }

        static std::shared_ptr<FileLogger> CreateFileBackend(const std::string& path,
                                                             bool               append = true)
        {
            auto logger = std::make_shared<FileLogger>(path, append);
            if (!logger->IsReady())
            {
                return nullptr;
            }
            return logger;
        }

        static bool InstallFileBackendSafe(const std::string& path, bool append = true)
        {
            auto logger = CreateFileBackend(path, append);
            if (!logger)
            {
                return false;
            }
            SetBackend(logger);
            return true;
        }

        template <typename... Args>
        static void Log(LogLevel         level,
                        const char*      file,
                        int              line,
                        const char*      func,
                        std::string_view fmt,
                        Args&&... args)
        {
            auto    tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::tm tm{};

            localtime_s(&tm, &tt);

            std::ostringstream time_ss;
            time_ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
            std::string timestamp = time_ss.str();

            std::string message = std::vformat(fmt, std::make_format_args(args...));

            auto backend = GetBackend();
            if (backend)
            {
                backend->Emit(level, timestamp, file ? file : "", line, func ? func : "", message);
            }
            else
            {
                std::cerr << "[" << timestamp << "] " << LogLevelToString(level) << " " << file
                          << ":" << line << " (" << func << "): " << message << std::endl;
            }
        }

      private:
        static std::shared_ptr<ILogger>& GetInstance()
        {
            static std::shared_ptr<ILogger> instance = std::make_shared<ConsoleLogger>();
            return instance;
        }
        static std::mutex& GetMutex()
        {
            static std::mutex mutex;
            return mutex;
        }
    };

#define LOG_INFO(fmt, ...)                                                                         \
    Logger::Log(LogLevel::Info, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...)                                                                      \
    Logger::Log(LogLevel::Warning, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)                                                                        \
    Logger::Log(LogLevel::Error, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

} // namespace insERT::logger
