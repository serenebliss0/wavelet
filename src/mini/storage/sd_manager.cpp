#include "sd_manager.h"
#include "mini/neopixel/NeoPixel.h"
#include "logger.h"

#include <FS.h>
#include <SD_MMC.h>

#define SD_CLK 38
#define SD_CMD 40
#define SD_D0  39
#define SD_D1  41
#define SD_D2  48
#define SD_D3  47

namespace
{
    bool sdMounted = false;
}

bool SDManager::begin()
{
    Serial.println("[SD] Initializing SD card...");

    // Configure SDMMC pins exactly as specified by the manufacturer
    if (!SD_MMC.setPins(SD_CLK, SD_CMD, SD_D0, SD_D1, SD_D2, SD_D3))
    {
        Serial.println("[SD] Pin configuration failed!");

        Logger::info("SD", "SD pin configuration failed");

        ledSetState(LedState::ERROR);
        return false;
    }

    Serial.println("[SD] Pins configured");

    // Initialize SD card
    if (!SD_MMC.begin())
    {
        Serial.println("[SD] Failed to mount");

        Logger::info("SD", "SD init failed to mount");

        ledSetState(LedState::ERROR);
        return false;
    }

    sdMounted = true;

    Serial.println("[SD] Mounted successfully");

    Logger::info("SD", "SD init successful");

    initializeFilesystem();

    return true;
}

bool SDManager::mounted()
{
    return sdMounted;
}

bool SDManager::exists(const char* path)
{
    if (!sdMounted)
        return false;

    return SD_MMC.exists(path);
}

bool SDManager::mkdir(const char* path)
{
    if (!sdMounted)
        return false;

    return SD_MMC.mkdir(path);
}

bool SDManager::initializeFilesystem()
{
    Serial.println("[SD] Initializing filesystem...");

    mkdir("/system");
    mkdir("/config");

    mkdir("/cache");
    mkdir("/cache/temp");
    mkdir("/cache/album_art");
    mkdir("/cache/weather");


    mkdir("/media");
    mkdir("/media/wallpapers");
    mkdir("/media/notifications");
    mkdir("/media/boot");


    mkdir("/logs");
    mkdir("/plugins");
    mkdir("/updates");

    Serial.println("[SD] Filesystem initialized");

    return true;
}

String SDManager::readFile(const char* path)
{
    if (!sdMounted)
        return "";

    File file = SD_MMC.open(path);

    if (!file)
        return "";

    String data = file.readString();

    file.close();

    return data;
}

bool SDManager::writeFile(const char* path, const String& data)
{
    if (!sdMounted)
        return false;

    File file = SD_MMC.open(path, FILE_WRITE);

    if (!file)
        return false;

    file.print(data);

    file.close();

    return true;
}

bool SDManager::appendFile(const char* path, const String& data)
{
    if (!sdMounted)
        return false;

    File file = SD_MMC.open(path, FILE_APPEND);

    if (!file)
        return false;

    file.print(data);

    file.close();

    return true;
}

// sd_manager.cpp — add near the other methods
File SDManager::openForWrite(const char* path)
{
    if (!sdMounted)
        return File(); // invalid/empty File, caller checks with if(!file)

    return SD_MMC.open(path, FILE_WRITE);
}