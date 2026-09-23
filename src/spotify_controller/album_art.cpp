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

    // Stream into a .tmp file, not the real destination. This is a
    // network-speed-dependent write that can take seconds — the exact
    // kind of long exposure window that turns a random power blip into
    // a corrupted file. The real file is only touched once the full
    // download is verified complete.
    String tempPath;
    File file = SDManager::openForWriteAtomic(path.c_str(), tempPath);
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
    bool writeError = false;

    while (http.connected() && (contentLength > 0 || contentLength == -1)) {
        size_t available = stream->available();
        if (available) {
            int bytesRead = stream->readBytes(buf, min(available, sizeof(buf)));
            size_t bytesWritten = file.write(buf, bytesRead);

            if (bytesWritten != (size_t)bytesRead) {
                Serial.println("[ART] Write error mid-download, aborting");
                Logger::error("Art", "Write error mid-download");
                writeError = true;
                break;
            }

            totalWritten += bytesWritten;
            if (contentLength > 0) {
                contentLength -= bytesRead;
            }
        }
        if (!stream->connected() && !available) break;
        delay(1);
    }

    file.flush();
    file.close();
    http.end();

    bool incomplete = (contentLength > 0 && contentLength != -1);

    if (writeError || incomplete) {
        // Download broke early or a write failed partway through —
        // throw away the .tmp file. The real file (old art, or nothing)
        // is never touched, so we don't end up with a half-saved image
        // silently passed off as "cached".
        SDManager::remove(tempPath.c_str());
        Serial.println("[ART] Download incomplete or write failed, discarding");
        return false;
    }

    if (!SDManager::commitAtomicWrite(path.c_str(), tempPath)) {
        Serial.println("[ART] Failed to commit album art file");
        Logger::error("Art", "Failed to commit album art file");
        return false;
    }

    Serial.printf("[ART] Saved %d bytes to %s
", totalWritten, path.c_str());
    return true;
}

void checkAndCacheAlbumArt(const String &albumId, JsonDocument &reply) {
    if (albumId == lastAlbumId) return;
    lastAlbumId = albumId;

    String path = albumArtPath(albumId);

    if (SDManager::exists(path.c_str())) {
        Serial.printf("[ART] Already cached: %s
", albumId.c_str());
        return;
    }

    String url = getAlbumArtUrl(reply);
    downloadAlbumArt(url, albumId);
}
