#include "logger.h"
#include "sd_manager.h"

static String levelToString(LogLevel level)
{
    switch(level)
    {
        case LogLevel::DEBUG:
            return "DEBUG";

        case LogLevel::INFO:
            return "INFO";

        case LogLevel::WARNING:
            return "WARNING";

        case LogLevel::ERROR:
            return "ERROR";
    }

    return "UNKNOWN";
}

static String getTimestamp()
{
    return String(millis());
}


void Logger::log(
    LogLevel level,
    const char* tag,
    const String& message)
{
    String line;

    line += "[";
    line += getTimestamp();
    line += "] ";

    line += "[";
    line += levelToString(level);
    line += "] ";

    line += "[";
    line += tag;
    line += "] ";

    line += message;

    #ifdef DEBUG
    Serial.println(line);
    #endif

    if(SDManager::mounted())
    {
        SDManager::appendFile(
            "/logs/system.log",
            line + "\n");
    }
}

void Logger::debug(
    const char* tag,
    const String& message)
{
    log(LogLevel::DEBUG, tag, message);
}

void Logger::info(
    const char* tag,
    const String& message)
{
    log(LogLevel::INFO, tag, message);
}

void Logger::warning(
    const char* tag,
    const String& message)
{
    log(LogLevel::WARNING, tag, message);
}


void Logger::error(
    const char* tag,
    const String& message)
{
    log(LogLevel::ERROR, tag, message);
}