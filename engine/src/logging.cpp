#include "phyber/logging.h"

#include <cstdarg>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

using namespace Phyber::Log;

#define ANSI_BLACK "\e[0;30m"
#define ANSI_RED "\e[0;31m"
#define ANSI_GREEN "\e[0;32m"
#define ANSI_YELLOW "\e[0;33m"
#define ANSI_BLUE "\e[0;34m"
#define ANSI_PURPLE "\e[0;35m"
#define ANSI_CYAN "\e[0;36m"
#define ANSI_WHITE "\e[0;37m"
#define ANSI_BG_BLACK "\e[0;40m"
#define ANSI_BG_RED "\e[0;41m"
#define ANSI_BG_GREEN "\e[0;42m"
#define ANSI_BG_YELLOW "\e[0;43m"
#define ANSI_BG_BLUE "\e[0;44m"
#define ANSI_BG_PURPLE "\e[0;45m"
#define ANSI_BG_CYAN "\e[0;46m"
#define ANSI_BG_WHITE "\e[0;47m"
#define ANSI_RESET "\e[0m"

static void get_formatted_time(char buffer[26]) {
    time_t timer;
    struct tm* tm_info;

    timer = time(NULL);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
}

static void print_level(Level level) {
    putchar('[');
    switch (level) {
    case Level::DEBUG:
        fputs(ANSI_BLUE, stdout);
        fputs("DEBUG", stdout);
        break;
    case Level::INFO:
        fputs(ANSI_GREEN, stdout);
        fputs("INFO", stdout);
        break;
    case Level::WARNING:
        fputs(ANSI_YELLOW, stdout);
        fputs("WARNING", stdout);
        break;
    case Level::ERROR:
        fputs(ANSI_RED, stdout);
        fputs("ERROR", stdout);
        break;
    case Level::CRITICAL:
        fputs(ANSI_WHITE ANSI_BG_RED, stdout);
        fputs("CRITICAL", stdout);
        break;
    }
    fputs(ANSI_RESET, stdout);
    putchar(']');
}

void Phyber::Log::printf_impl(Level level, const char *file, unsigned int line, const char *format, ...) {
    va_list args;
    va_start(args, format);

    char timefmt[26];
    get_formatted_time(timefmt);

    print_level(level);
    putchar(' ');
    fputs(file, stdout);
    printf(":%u (", line);
    fputs(timefmt, stdout);
    fputs(") " ANSI_PURPLE "->" ANSI_RESET " ", stdout);
    vprintf(format, args);
    putchar('\n');

    va_end(args);
}
