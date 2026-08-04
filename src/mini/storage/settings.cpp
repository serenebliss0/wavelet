#include "settings.h"

#include <ArduinoJson.h>

#include "logger.h"
#include "sd_manager.h"

static SettingsData settings;

bool Settings::begin()
{
    if(!SDManager::exists("/config/settings.json"))
    {
        Logger::warning(
            "Settings",
            "settings.json missing, creating defaults.");

        reset();

        return save();
    }

    return load();
}

void Settings::reset()
{
    settings = SettingsData();
}


SettingsData& Settings::get()
{
    return settings;
}


bool Settings::save()
{
    JsonDocument doc;

    doc["version"] = settings.version;

    doc["deviceName"] = settings.deviceName;

    doc["brightness"] = settings.brightness;
    doc["volume"] = settings.volume;

    doc["ledEnabled"] = settings.ledEnabled;

    doc["twentyFourHour"] = settings.twentyFourHour;

    doc["timezone"] = settings.timezone;

    doc["shuffle"] = settings.shuffle;
    doc["repeat"] = settings.repeat;

    String json;

    serializeJsonPretty(doc, json);

    if(!SDManager::writeFile(
        "/config/settings.json",
        json))
    {
        Logger::error(
            "Settings",
            "Failed to save settings.");

        return false;
    }

    Logger::info(
        "Settings",
        "Settings saved.");

    return true;
}

bool Settings::load()
{
    String json =
        SDManager::readFile("/config/settings.json");

    if(json.isEmpty())
        return false;

    JsonDocument doc;

    if(deserializeJson(doc, json))
    {
        Logger::error(
            "Settings",
            "Invalid JSON.");

        return false;
    }

    settings.version =
        doc["version"] | 1;

    settings.deviceName =
        doc["deviceName"] | "Wavelet Mini";

    settings.brightness =
        doc["brightness"] | 100;

    settings.volume =
        doc["volume"] | 50;

    settings.ledEnabled =
        doc["ledEnabled"] | true;

    settings.twentyFourHour =
        doc["twentyFourHour"] | true;

    settings.timezone =
        doc["timezone"] | "Africa/Lagos";

    settings.shuffle =
        doc["shuffle"] | false;

    settings.repeat =
        doc["repeat"] | false;

    Logger::info(
        "Settings",
        "Settings loaded.");

    return true;
}