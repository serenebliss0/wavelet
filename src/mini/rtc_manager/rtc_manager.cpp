#include "rtc_manager.h"

#include <cstring>
#include <sys/time.h>

namespace
{
    String formatLocalTime(const char* format, const char* invalidValue)
    {
        if (!RTC::isValid())
            return invalidValue;

        const time_t timestamp = RTC::now();
        tm localTime;

        if (localtime_r(&timestamp, &localTime) == nullptr)
            return invalidValue;

        char buffer[32];
        if (strftime(buffer, sizeof(buffer), format, &localTime) == 0)
            return invalidValue;

        return String(buffer);
    }

    const char* toEspTimezone(const char* timezone)
    {
        // ESP-IDF/newlib accepts POSIX TZ strings, not the full IANA timezone
        // database. Keep the IANA name already used in settings working.
        if (std::strcmp(timezone, "Africa/Lagos") == 0)
            return "WAT-1";

        if (std::strcmp(timezone, "UTC") == 0 ||
            std::strcmp(timezone, "Etc/UTC") == 0)
            return "UTC0";

        return timezone;
    }
}

namespace RTC
{
    bool begin(const char* timezone)
    {
        return setTimezone(timezone);
    }

    bool setTimezone(const char* timezone)
    {
        // An empty TZ value is ambiguous and makes local-time output fragile.
        if (timezone == nullptr || timezone[0] == '\0')
            return false;

        if (setenv("TZ", toEspTimezone(timezone), 1) != 0)
            return false;

        tzset();
        return true;
    }

    void setTime(time_t timestamp)
    {
        const timeval value = {
            .tv_sec = timestamp,
            .tv_usec = 0,
        };

        settimeofday(&value, nullptr);
    }

    time_t now()
    {
        return time(nullptr);
    }

    bool isValid()
    {
        return now() >= MIN_VALID_UNIX_TIME;
    }

    String timeString()
    {
        return formatLocalTime("%H:%M:%S", "--:--:--");
    }

    String dateString()
    {
        return formatLocalTime("%d %b %Y", "-- --- ----");
    }

    String dateTimeString()
    {
        return formatLocalTime("%d %b %Y %H:%M:%S", "Invalid time");
    }

    String getTime()
    {
        return timeString();
    }

    String getDate()
    {
        return dateString();
    }

    String getDateTime()
    {
        return dateTimeString();
    }
}
