// album_art.cpp
#include "album_art.h"
#include "mini/storage/sd_manager.h"
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "mini/storage/logger.h"

static String lastAlbumId = "";

static String albumArtPath(const String &albumId) {
    return "/cache/album_art/" + albumId + ".jpg";
}

static String getAlbumArtUrl(JsonDocument &reply) {
    JsonArray images = reply["item"]["album"]["images"].as<JsonArray>();
    for (JsonObject img : images) {
        if (img["width"] == 300) {
            return img["url"].as<String>();
        }
    }
    if (images.size() > 0) {
        return images[0]["url"].as<String>();
    }
    return "";
}

static bool downloadAlbumArt(const String &url, const String &albumId) {
    if (url.isEmpty()) {
        Serial.println("[ART] No URL to download");
        return false;
    }

    String path = albumArtPath(albumId);

    Serial.printf("[ART] Downloading: %s\n", url.c_str());

    HTTPClient http;
    http.begin(url.c_str());

    int httpCode = http.GET();

    if (httpCode != HTTP_CODE_OK) {
        Serial.printf("[ART] Download failed, HTTP %d\n", httpCode);
        http.end();
        return false;
    }

    File file = SDManager::openForWrite(path.c_str());
    if (!file) {
        Serial.println("[ART] Failed to open file for writing");
        Logger::error("Art", "Failed to open file for writing");
        http.end();
        return false;
    }

    WiFiClient *stream = http.getStreamPtr();
    uint8_t buf[512];

    size_t totalWritten = 0;
    int contentLength = http.getSize();
    
    while (http.connected() && (contentLength > 0 || contentLength == -1)) {
        size_t available = stream->available();
        if (available) {
            int bytesRead = stream->readBytes(buf, min(available, sizeof(buf)));
            file.write(buf, bytesRead);
            totalWritten += bytesRead;
            if (contentLength > 0) {
                contentLength -= bytesRead;
            }
        }
        if (!stream->connected() && !available) break;
        delay(1);
    }

    file.close();
    http.end();

    Serial.printf("[ART] Saved %d bytes to %s\n", totalWritten, path.c_str());
    return true;
}

void checkAndCacheAlbumArt(const String &albumId, JsonDocument &reply) {
    if (albumId == lastAlbumId) return;
    lastAlbumId = albumId;

    String path = albumArtPath(albumId);

    if (SDManager::exists(path.c_str())) {
        Serial.printf("[ART] Already cached: %s\n", albumId.c_str());
        return;
    }

    String url = getAlbumArtUrl(reply);
    downloadAlbumArt(url, albumId);
}