#pragma once

#include <Arduino.h>
#include <time.h>

/**
 * ESP32-S3 internal RTC clock helpers.
 *
 * The clock survives deep sleep, but not a complete loss of power.  Time is
 * deliberately not synchronised here: another layer (BLE, Wi-Fi, etc.) should
 * call setTime() whenever it obtains an authoritative Unix timestamp.
 */
namespace RTC
{
    constexpr time_t MIN_VALID_UNIX_TIME = 1700000000;

    /** Configure local-time conversion. Call after Settings::begin(). */
    bool begin(const char* timezone = "UTC");

    /**
     * Set the timezone used by the formatting functions.
     *
     * ESP-IDF uses POSIX TZ strings (for example, "WAT-1").  The persisted
     * Mini default, "Africa/Lagos", is accepted as a convenience alias.
     */
    bool setTimezone(const char* timezone);

    /** Set the ESP32 system clock from a UTC Unix timestamp. */
    void setTime(time_t timestamp);

    /** Return the current UTC Unix timestamp. */
    time_t now();

    /** True once the system clock has been set to a plausible modern time. */
    bool isValid();

    /** Local-time display strings. Invalid clocks return display-safe values. */
    String timeString();      // HH:MM:SS
    String dateString();      // DD Mon YYYY
    String dateTimeString();  // DD Mon YYYY HH:MM:SS

    // Temporary compatibility aliases for existing Mini callers.
    String getTime();
    String getDate();
    String getDateTime();
}
