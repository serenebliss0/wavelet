#pragma once
#include <Arduino.h>
#include <Preferences.h>
#include <lvgl.h>
#include "mini/storage/logger.h"

// ── Token ─────────────────────────────────────────────────────────────────────
String getOrCreateSetupToken() {
    Preferences prefs;
    prefs.begin("wavelet", false);

    String token = prefs.getString("setup_token", "");

    if (token.isEmpty()) {
        const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        randomSeed(esp_random());
        for (int i = 0; i < 8; i++) {
            token += charset[random(0, 36)];
        }
        prefs.putString("setup_token", token);
        Serial.printf("[QR] Generated new token: %s\n", token.c_str());
    }

    prefs.end();
    return token;
}

// Payload
String buildQRPayload(String deviceId, String color) {
    String token = getOrCreateSetupToken();

    return "wavelet://setup?model=mini&id=" + deviceId +
           "&token=" + token +
           "&color=" + color;
}

// Generate the QR Code
// returns false if generation failed
bool generateQR(const char* payload, uint8_t*, uint8_t*) {
    return payload != nullptr;
}

// Render in serial for testing
void printQRToSerial(const String& payload) {
    Serial.println("[QR] Payload:");
    Serial.println(payload);
    Serial.println("[QR] Rendering handled by LVGL QR widget.");
}


// Render on display
void renderQRToDisplay(String payload, lv_obj_t* parent) {

    const int qrPx = 145;

    // white background behind QR for contrast
    lv_obj_t* bg = lv_obj_create(parent);
    lv_obj_set_size(bg, qrPx + 16, qrPx + 16);
    lv_obj_center(bg);
    lv_obj_set_y(bg, -16);

    lv_obj_set_style_bg_color(bg, lv_color_hex(0xFAF1F9), 0);
    lv_obj_set_style_border_width(bg, 0, 0);
    lv_obj_set_style_radius(bg, 8, 0);
    lv_obj_clear_flag(bg, LV_OBJ_FLAG_SCROLLABLE);

    // QR widget
    lv_obj_t* qr = lv_qrcode_create(
        bg,
        qrPx,
        lv_color_hex(0x0D0D0D),
        lv_color_hex(0xFAF1F9)
    );

    lv_obj_center(qr);

    lv_res_t res = lv_qrcode_update(
        qr,
        payload.c_str(),
        payload.length()
    );

    if (res != LV_RES_OK) {
        Serial.println("[QR] Generation failed!");
    }
}


// ── Main Entry
void showSetupQR(String deviceId, String color, lv_obj_t* parent) {

    String payload = buildQRPayload(deviceId, color);

#ifdef DEBUG
    printQRToSerial(payload);
#endif

    renderQRToDisplay(payload, parent);
}