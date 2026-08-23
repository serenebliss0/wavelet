// album_art.h
#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

void checkAndCacheAlbumArt(const String &albumId, JsonDocument &reply);