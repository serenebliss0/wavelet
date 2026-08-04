#include "sd_manager.h"
#include "mini/neopixel/NeoPixel.h"
#include "logger.h"

#include <FS.h>
#include <SD.h>

namespace
{
    bool sdMounted = false;
}

bool SDManager::begin()
{
    sdMounted = SD.begin();

    if(!sdMounted)
    {   
        #ifdef DEBUG
        Serial.println("[SD] Failed to mount");
        Logger::info("SD", "SD init failed to mount")

        #endif
        ledSetState(LedState::ERROR);
        return false;
    }

    #ifdef DEBUG
    Serial.println("[SD] Mounted");
    Logger::info("SD", "SD init successful")
    #endif

    initializeFilesystem();

    return true;
}

bool SDManager::mounted()
{
    return sdMounted;
}

bool SDManager::exists(const char* path)
{
    if(!sdMounted)
        return false;

    return SD.exists(path);
}

bool SDManager::mkdir(const char* path)
{
    if(!sdMounted)
        return false;

    return SD.mkdir(path);
}

bool SDManager::initializeFilesystem()
{
    mkdir("/system");
    mkdir("/config");
    mkdir("/cache");
    mkdir("/media");
    mkdir("/logs");
    mkdir("/updates");

    return true;
}

String SDManager::readFile(const char* path)
{
    File file = SD.open(path);

    if(!file)
        return "";

    String data = file.readString();

    file.close();

    return data;
}

bool SDManager::writeFile(const char* path, const String& data)
{
    File file = SD.open(path, FILE_WRITE);

    if(!file)
        return false;

    file.print(data);

    file.close();

    return true;
}

bool SDManager::appendFile(const char* path, const String& data)
{
    File file = SD.open(path, FILE_APPEND);

    if(!file)
        return false;

    file.print(data);

    file.close();

    return true;
}