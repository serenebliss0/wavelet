#include "album_art.h"

#include <HTTPClient.h>
#include <SD_MMC.h>
#include <TJpg_Decoder.h>
#include <WiFi.h>
#include <esp_heap_caps.h>
#include <lvgl.h>

#include "mini/wavelet-mini-screens/src/ui/images.h"
#include "mini/wavelet-mini-screens/src/ui/screens.h"
#include "mini/storage/sd_manager.h"

namespace {
constexpr uint16_t kCoverSize = 118;
constexpr size_t kMaxJpegBytes = 72 * 1024;
String lastAlbumId;
String requestedUrl;
String requestedAlbumId;
bool requestInProgress = false;
bool artEnabled = true;
uint16_t *decodePixels = nullptr;
uint16_t *pendingPixels = nullptr;
uint16_t *displayedPixels = nullptr;
uint16_t *retiredPixels = nullptr;
uint32_t retireAt = 0;
lv_img_dsc_t displayedImage = {};

bool jpgBlock(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *pixels) {
    if (!decodePixels) return false;
    for (uint16_t row = 0; row < h; ++row) {
        const int py = y + row;
        if (py < 0 || py >= kCoverSize) continue;
        for (uint16_t col = 0; col < w; ++col) {
            const int px = x + col;
            if (px >= 0 && px < kCoverSize) decodePixels[py * kCoverSize + px] = pixels[row * w + col];
        }
    }
    return true;
}

void artTask(void *) {
    uint16_t *pixels = static_cast<uint16_t *>(heap_caps_calloc(kCoverSize * kCoverSize, sizeof(uint16_t), MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT));
    if (!pixels) {
        requestInProgress = false;
        vTaskDelete(nullptr);
        return;
    }

    const String cachePath = String("/cache/album_art/") + requestedAlbumId + ".jpg";
    uint8_t *jpeg = nullptr;
    int length = 0;

    // Keep the established persistent SD cache. Only fetch from the network
    // when the card is absent or this album has not been cached yet.
    if (SDManager::mounted() && SDManager::exists(cachePath.c_str())) {
        File cached = SD_MMC.open(cachePath.c_str(), FILE_READ);
        if (cached && cached.size() > 0 && cached.size() <= kMaxJpegBytes) {
            length = cached.size();
            jpeg = static_cast<uint8_t *>(heap_caps_malloc(length, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT));
            if (jpeg && cached.read(jpeg, length) != (size_t)length) {
                heap_caps_free(jpeg);
                jpeg = nullptr;
            }
        }
        cached.close();
    }

    if (!jpeg) {
        HTTPClient http;
        http.setTimeout(5000);
        http.begin(requestedUrl);
        const int code = http.GET();
        const int contentLength = http.getSize();
        if (code == HTTP_CODE_OK && contentLength > 0 && contentLength <= (int)kMaxJpegBytes) {
            length = contentLength;
            jpeg = static_cast<uint8_t *>(heap_caps_malloc(length, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT));
        if (jpeg) {
            WiFiClient *stream = http.getStreamPtr();
            size_t received = 0;
            const uint32_t deadline = millis() + 5000;
            while (received < (size_t)length && millis() < deadline) {
                const int available = stream->available();
                if (available > 0) received += stream->readBytes(jpeg + received, min((size_t)available, (size_t)length - received));
                else if (!http.connected()) break;
                else vTaskDelay(pdMS_TO_TICKS(10));
            }
            if (received != (size_t)length) {
                heap_caps_free(jpeg);
                jpeg = nullptr;
            } else if (SDManager::mounted()) {
                File cache = SDManager::openForWrite(cachePath.c_str());
                if (cache) {
                    cache.write(jpeg, length);
                    cache.close();
                    Serial.printf("[ART] Cached %d bytes to SD\n", length);
                }
            }
        }
        }
        http.end();
    }

    if (jpeg && artEnabled) {
        decodePixels = pixels;
        TJpgDec.setJpgScale(2);
        TJpgDec.setCallback(jpgBlock);
        TJpgDec.drawJpg(0, 0, jpeg, length);
        decodePixels = nullptr;
        heap_caps_free(jpeg);
        if (artEnabled) pendingPixels = pixels;
        else heap_caps_free(pixels);
    } else {
        if (jpeg) heap_caps_free(jpeg);
        heap_caps_free(pixels);
    }
    requestInProgress = false;
    vTaskDelete(nullptr);
}

String findImageUrl(JsonDocument &reply) {
    JsonArray images = reply["item"]["album"]["images"].as<JsonArray>();
    String fallback;
    for (JsonObject image : images) {
        const String url = image["url"].as<String>();
        const int width = image["width"] | 0;
        if (width == 300) return url;
        if (fallback.isEmpty() && !url.isEmpty()) fallback = url;
    }
    return fallback;
}
}

void checkAndCacheAlbumArt(const String &albumId, JsonDocument &reply) {
    if (!artEnabled || albumId.isEmpty() || albumId == lastAlbumId || requestInProgress || !WiFi.isConnected()) return;
    requestedUrl = findImageUrl(reply);
    if (requestedUrl.isEmpty()) return;
    requestedAlbumId = albumId;
    lastAlbumId = albumId;
    requestInProgress = true;
    if (xTaskCreatePinnedToCore(artTask, "albumArt", 8192, nullptr, 1, nullptr, 0) != pdPASS) requestInProgress = false;
}

void albumArtSetEnabled(bool enabled) {
    artEnabled = enabled;
    if (!enabled) {
        lastAlbumId = "";
        if (pendingPixels) { heap_caps_free(pendingPixels); pendingPixels = nullptr; }
        if (objects.album_cover) lv_img_set_src(objects.album_cover, &img_default_album_cover);
        if (displayedPixels) {
            if (retiredPixels) heap_caps_free(retiredPixels);
            retiredPixels = displayedPixels;
            displayedPixels = nullptr;
            retireAt = millis() + 500;
        }
    }
}

void albumArtProcessUi() {
    if (retiredPixels && (int32_t)(millis() - retireAt) >= 0) {
        heap_caps_free(retiredPixels);
        retiredPixels = nullptr;
    }
    if (!pendingPixels || !artEnabled || !objects.album_cover) return;
    uint16_t *next = pendingPixels;
    pendingPixels = nullptr;
    displayedImage.header.always_zero = 0;
    displayedImage.header.w = kCoverSize;
    displayedImage.header.h = kCoverSize;
    displayedImage.header.cf = LV_IMG_CF_TRUE_COLOR;
    displayedImage.data_size = kCoverSize * kCoverSize * sizeof(uint16_t);
    displayedImage.data = reinterpret_cast<const uint8_t *>(next);
    lv_img_set_src(objects.album_cover, &displayedImage);
    if (displayedPixels) {
        if (retiredPixels) heap_caps_free(retiredPixels);
        retiredPixels = displayedPixels;
        retireAt = millis() + 500;
    }
    displayedPixels = next;
}

bool albumArtIsBusy() { return requestInProgress; }
