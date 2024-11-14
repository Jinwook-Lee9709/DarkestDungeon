#define _CRT_SECURE_NO_WARNINGS
#ifndef __FZ_VEGA_HEADER_H_
#define __FZ_VEGA_HEADER_H_
#pragma once
#include <iostream>
#include <ctime>
#include <sstream>
#include <vector>
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN

namespace _internal {
    namespace Realog {

        static void convert_unicode_to_ansi_string(
            std::string& ansi,
            const wchar_t* unicode,
            const size_t unicode_size
        ) {
            do {

                if ((nullptr == unicode) || (0 == unicode_size)) {
                    break;
                }
                ansi.clear();
                int required_cch = ::WideCharToMultiByte(
                    CP_ACP,
                    0,
                    unicode, static_cast<int>(unicode_size),
                    nullptr, 0,
                    nullptr, nullptr
                );
                if (0 == required_cch) {
                    break;
                }
                ansi.resize(required_cch);
                if (0 == ::WideCharToMultiByte(
                    CP_ACP,
                    0,
                    unicode, static_cast<int>(unicode_size),
                    const_cast<char*>(ansi.c_str()), static_cast<int>(ansi.size()),
                    nullptr, nullptr
                )) {
                    break;
                }
            } while (false);
            return;
        }
        
        struct NoArg {};

        inline std::ostream& operator<<(std::ostream& stream, const NoArg& arg)
        {
            return stream;
        }

        class Util
        {
        public:
            Util() = delete;

            static void replaceAll(std::string& string, const std::string& replace, const std::string& with)
            {
                size_t pos = string.find(replace);

                while (pos != std::string::npos)
                {
                    string.replace(pos, replace.size(), with);
                    pos = string.find(replace, pos + with.size());
                }
            }

            template<typename... Args>
            static std::vector<std::string> convertArgsToStringVector(const Args&... args)
            {
                std::vector<std::string> vector;

                iterate(vector, NoArg(), args...);

                return vector;
            }

        private:
            template<typename T, typename... Args>
            static void iterate(std::vector<std::string>& vector, T first, const Args&... args)
            {
                iterate(vector, first);
                iterate(vector, args...);
            }

            template<typename T>
            static void iterate(std::vector<std::string>& vector, T t)
            {
                if (!std::is_same<T, NoArg>::value) {
                    std::stringstream stream;
                    stream << t;
                    vector.push_back(stream.str());
                }
            }
        };

        enum class Level
        {
            Trace, Debug, Info, Warn, Error, Critical
        };

        class Logger
        {
        public:
            Logger(const std::string& name = "FZLogger", const Level& level = Level::Trace)
                : m_name(name), m_level(level)
            {}

            Logger(const Logger& other) = delete;
            Logger& operator=(const Logger& other) = delete;

            inline void setName(const std::string& name) { m_name = name; }

            template<typename... Args>
            inline void trace(const std::string& message, const Args&... args)
            {
                log(message, Level::Trace, Util::convertArgsToStringVector(args...));
            }

            template<typename... Args>
            inline void debug(const std::string& message, const Args&... args)
            {
                log(message, Level::Debug, Util::convertArgsToStringVector(args...));
            }

            template<typename... Args>
            inline void info(const std::string& message, const Args&... args)
            {
                log(message, Level::Info, Util::convertArgsToStringVector(args...));
            }

            template<typename... Args>
            inline void warn(const std::string& message, const Args&... args)
            {
                log(message, Level::Warn, Util::convertArgsToStringVector(args...));
            }

            template<typename... Args>
            inline void error(const std::string& message, const Args&... args)
            {
                log(message, Level::Error, Util::convertArgsToStringVector(args...));
            }

            template<typename... Args>
            inline void critical(const std::string& message, const Args&... args)
            {
                log(message, Level::Critical, Util::convertArgsToStringVector(args...));
            }

            template<typename... Args>
            inline void log(const std::string& message, const Args&... args)
            {
                log(message, m_level, Util::convertArgsToStringVector(args...));
            }

            inline void setLevel(const Level& level)
            {
                m_level = level;
            }

        private:
            void log(const std::string& message, const Level& level, const std::vector<std::string>& args)
            {
                time_t now = time(0);
                std::tm ltm;
                localtime_s(&ltm, &now);

                switch (level)
                {
                case Level::Trace:
                    std::cout << "\033[0m";
                    break;
                case Level::Debug:
                    std::cout << "\033[0;34m";
                    break;
                case Level::Info:
                    std::cout << "\033[0;32m";
                    break;
                case Level::Warn:
                    std::cout << "\033[0;33m";
                    break;
                case Level::Error:
                    std::cout << "\033[0;31m";
                    break;
                case Level::Critical:
                    std::cout << "\033[0;41m";
                    break;
                };

                auto result = build(message, args);

                std::cout << "["
                    << (ltm.tm_hour < 10 ? "0" : "") << ltm.tm_hour << ":"
                    << (ltm.tm_min < 10 ? "0" : "") << ltm.tm_min << ":"
                    << (ltm.tm_sec < 10 ? "0" : "") << ltm.tm_sec << "] "
                    << m_name << ": "
                    << result;

                std::cout << "\033[0m" << std::endl;
            }

            std::string build(const std::string& message, const std::vector<std::string>& args)
            {
                std::string result = message;

                for (size_t i = 0; i < args.size(); ++i) {
                    std::stringstream ss;
                    ss << '{' << i << '}';
                    Util::replaceAll(result, ss.str(), args[i]);
                }

                return result;
            }

        private:
            std::string m_name;
            Level m_level;
        };
    }
}
namespace fz {
    class Logger
    {
    public:
        template <typename ...Args>
        static void Trace(Args&& ...args) {
            s_Logger.trace(std::forward<Args>(args)...);
        }

        template <typename ...Args>
        static void Debug(Args&& ...args) {
            s_Logger.debug(std::forward<Args>(args)...);
        }

        template <typename ...Args>
        static void Info(Args&& ...args) {
            s_Logger.info(std::forward<Args>(args)...);
        }

        template <typename ...Args>
        static void Warn(Args&& ...args) {
            s_Logger.warn(std::forward<Args>(args)...);
        }

        template <typename ...Args>
        static void Error(Args&& ...args) {
            s_Logger.error(std::forward<Args>(args)...);
        }

        template <typename ...Args>
        static void Critical(Args&& ...args) {
            s_Logger.critical(std::forward<Args>(args)...);
        }

        static void SetName(const std::string& name) {
            s_Logger.setName(name);
        }

    private:
        inline static _internal::Realog::Logger s_Logger;
    };
}

/**
 * @def FZLOG_DEBUG_MODE_ENABLED
 *
 * @brief ����� ��忡���� �α� �ý����� Ȱ��ȭ�մϴ�.
 *
 * Example usage:
 * @code
 *      #define FZLOG_DEBUG_MODE_ENABLED
 *      FZLOG_TRACE("Test FZLog");
 * @endcode
 *
 * @note 
 * - ���� ����� ����� �� �α� �ý����� ��Ȱ��ȭ�ϰ��� �ϴ� ��쿡�� �ش� ��ũ�θ� �������ּ���.
 * - FZLOG_DEBUG_MODE_ENABLED�� ���� �����ϴ� FZLog.hpp�� ��ܿ� ��ġ�ؾ� �մϴ�. 
 */
#if defined(_DEBUG) || defined(FZLOG_DEBUG_MODE_ENABLED)
    #define FZLOG_TRACE(...)                { fz::Logger::Trace(__VA_ARGS__); }
    #define FZLOG_DEBUG(...)                { fz::Logger::Debug(__VA_ARGS__); }
    #define FZLOG_INFO(...)                 { fz::Logger::Info(__VA_ARGS__); }
    #define FZLOG_WARN(...)                 { fz::Logger::Warn(__VA_ARGS__); }
    #define FZLOG_ERROR(...)                { fz::Logger::Error(__VA_ARGS__); }
    #define FZLOG_CRITICAL(...)             { fz::Logger::Critical(__VA_ARGS__); }
    #define FZLOG_ASSERT(flag, ...)         { if(!(flag)) { fz::Logger::Error(__VA_ARGS__); DebugBreak();} }
#else
    #define FZLOG_TRACE(...)       
    #define FZLOG_DEBUG(...)       
    #define FZLOG_INFO(...)        
    #define FZLOG_WARN(...)        
    #define FZLOG_ERROR(...)       
    #define FZLOG_CRITICAL(...)    
    #define FZLOG_ASSERT(flag, ...)
#endif

#endif /* defined(__FZ_VEGA_HEADER_H_) */