#ifndef PHYBER_ENGINE_LOGGING_H
#define PHYBER_ENGINE_LOGGING_H

#include <cstdarg>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

namespace Phyber {
namespace Log {

enum class Level : uint8_t {
    DEBUG, INFO, WARNING, ERROR, CRITICAL
};

extern void printf_impl(Level level, const char *file, unsigned int line, const char *format, ...);


}
}

#define PHYBER_LOG_DEBUG(format, ...) Phyber::Log::printf_impl(Phyber::Log::Level::DEBUG, __FILE__, __LINE__, (format), __VA_ARGS__)
#define PHYBER_LOG_INFO(format, ...) Phyber::Log::printf_impl(Phyber::Log::Level::INFO, __FILE__, __LINE__, (format), __VA_ARGS__)
#define PHYBER_LOG_WARNING(format, ...) Phyber::Log::printf_impl(Phyber::Log::Level::WARNING, __FILE__, __LINE__, (format), __VA_ARGS__)
#define PHYBER_LOG_ERROR(format, ...) Phyber::Log::printf_impl(Phyber::Log::Level::ERROR, __FILE__, __LINE__, (format), __VA_ARGS__)
#define PHYBER_LOG_CRITICAL(format, ...) Phyber::Log::printf_impl(Phyber::Log::Level::CRITICAL, __FILE__, __LINE__, (format), __VA_ARGS__)


#endif /* PHYBER_ENGINE_LOGGING_H */
