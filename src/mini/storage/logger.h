#pragma once
#include <Arduino.h>

enum class LogLevel
{
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

namespace Logger
{
    void begin();

    void debug(const char* tag, const String& message);
    void info(const char* tag, const String& message);
    void warning(const char* tag, const String& message);
    void error(const char* tag, const String& message);

    void log(
            LogLevel level,
            const char* tag,
            const String& message);
}