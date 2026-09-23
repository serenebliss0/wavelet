#include "sd_manager.h"
#include "mini/neopixel/NeoPixel.h"
#include "logger.h"
#include "mini/MiniConfig.h"

#include <FS.h>
#include <SD_MMC.h>

namespace
{
    bool sdMounted = false;
}

bool SDManager::begin()
{
    Serial.println("[SD] Initializing SD card...");
    Logger::info("SD", "Starting SD Init");

    // Configure SDMMC pins exactly as specified by the manufacturer
    if (!SD_MMC.setPins(SD_CLK, SD_CMD, SD_D0, SD_D1, SD_D2, SD_D3))
    {
        Serial.println("[SD] Pin configuration failed!");
        Logger::info("SD", "SD pin configuration failed");

        ledSetState(LedState::ERROR);
        return false;
    }

    Serial.println("[SD] Pins configured");
    Logger::info("SD", "SD Pins Configured");

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

bool SDManager::end()
{
    if (!sdMounted)
        return true;

    SD_MMC.end();
    sdMounted = false;

    Serial.println("[SD] Unmounted cleanly");
    Logger::info("SD", "SD unmounted cleanly");

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

bool SDManager::remove(const char* path)
{
    if (!sdMounted)
        return false;

    return SD_MMC.remove(path);
}

bool SDManager::initializeFilesystem()
{
    Serial.println("[SD] Initializing filesystem...");
    Logger::info("SD", "Initializing filesystem");

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
    Logger::info("SD", "Filesystem initialized");

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

File SDManager::openForWriteAtomic(const char* path, String& outTempPath)
{
    if (!sdMounted)
        return File();

    outTempPath = String(path) + ".tmp";

    // Clear out any stale temp file left behind by a previous write
    // that never got committed (e.g. the last power interruption).
    if (SD_MMC.exists(outTempPath))
        SD_MMC.remove(outTempPath);

    return SD_MMC.open(outTempPath, FILE_WRITE);
}

bool SDManager::commitAtomicWrite(const char* finalPath, const String& tempPath)
{
    if (!sdMounted)
        return false;

    if (!SD_MMC.exists(tempPath))
    {
        Logger::error("SD", "Atomic commit: temp file missing");
        return false;
    }

    // Only touch the real file once we know the replacement is ready.
    if (SD_MMC.exists(finalPath))
    {
        if (!SD_MMC.remove(finalPath))
        {
            Logger::error("SD", "Atomic commit: failed to remove old file");
            return false;
        }
    }

    if (!SD_MMC.rename(tempPath.c_str(), finalPath))
    {
        Logger::error("SD", "Atomic commit: rename failed");
        return false;
    }

    return true;
}

bool SDManager::writeFile(const char* path, const String& data)
{
    if (!sdMounted)
        return false;

    String tempPath;
    File file = openForWriteAtomic(path, tempPath);

    if (!file)
        return false;

    size_t written = file.print(data);

    file.flush();
    file.close();

    if (written != data.length())
    {
        Logger::error("SD", "writeFile: short write, discarding temp file");
        SD_MMC.remove(tempPath);
        return false;
    }

    if (!commitAtomicWrite(path, tempPath))
    {
        Logger::error("SD", "writeFile: commit failed");
        return false;
    }

    return true;
}

bool SDManager::appendFile(const char* path, const String& data)
{
    if (!sdMounted)
        return false;

    File file = SD_MMC.open(path, FILE_APPEND);

    if (!file)
        return false;

    size_t written = file.print(data);

    file.flush();
    file.close();

    return written == data.length();
}

File SDManager::openForWrite(const char* path)
{
    if (!sdMounted)
        return File();

    return SD_MMC.open(path, FILE_WRITE);
}
