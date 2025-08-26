#pragma once

#include <iostream>

#include "ILogger.h"

namespace insERT::logger
{

    class ConsoleLogger : public ILogger
    {
      public:
        void Emit(LogLevel           level,
                  const std::string& timestamp,
                  const char*        file,
                  int                line,
                  const char*        func,
                  const std::string& message) override
        {
            std::cout << "[" << timestamp << "] " << LogLevelToString(level) << " " << file << ":"
                      << line << " (" << func << "): " << message << '\n';
        }
    };

} // namespace insERT::logger
