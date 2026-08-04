#pragma once

#include <Arduino.h>

namespace SDManager
{
    bool begin();

    bool mounted();

    bool exists(const char* path);

    bool mkdir(const char* path);

    bool remove(const char* path);

    bool initializeFilesystem();

    String readFile(const char* path);

    bool writeFile(const char* path, const String& data);

    bool appendFile(const char* path, const String& data);
}