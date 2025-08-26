#pragma once

#include <fstream>
#include <iostream>
#include <mutex>

#include "ILogger.h"

namespace insERT::logger
{

    class FileLogger : public ILogger
    {
      public:
        explicit FileLogger(const std::string& path, bool append = true) noexcept
        {
            std::ios_base::openmode mode = append ? (std::ios::out | std::ios::app) : std::ios::out;
            m_outStream.open(path, mode);

            if (m_outStream)
            {
                m_isReady = true;
            }
        }

        bool IsReady() const noexcept
        {
            return m_isReady;
        }

        void Emit(LogLevel           level,
                  const std::string& timestamp,
                  const char*        file,
                  int                line,
                  const char*        func,
                  const std::string& message) override
        {
            std::scoped_lock lock(m_mutex);
            if (!m_isReady)
            {
                std::cerr << "[" << timestamp << "] " << LogLevelToString(level) << " " << file
                          << ":" << line << " (" << func << "): " << message << '\n';
                return;
            }

            m_outStream << "[" << timestamp << "] " << LogLevelToString(level) << " " << file << ":"
                        << line << " (" << func << "): " << message << '\n';
            m_outStream.flush();
        }

      private:
        std::ofstream m_outStream;
        std::mutex    m_mutex;
        bool          m_isReady{};
    };

} // namespace insERT::logger
