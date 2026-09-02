#include "qr_setup.h"

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

// Main Entry
void showSetupQR(String deviceId, String color, lv_obj_t* parent) {

    String payload = buildQRPayload(deviceId, color);

#ifdef DEBUG
    printQRToSerial(payload);
#endif
}