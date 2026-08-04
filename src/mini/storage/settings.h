#pragma once

#include <Arduino.h>

struct SettingsData
{
    uint8_t version = 1;

    String deviceName = "Wavelet Mini";

    uint8_t brightness = 100;
    uint8_t volume = 50;

    bool ledEnabled = true;

    bool twentyFourHour = true;

    String timezone = "Africa/Lagos";

    bool shuffle = false;
    bool repeat = false;
};

namespace Settings
{
    bool begin();

    bool load();

    bool save();

    SettingsData& get();

    void reset();
}