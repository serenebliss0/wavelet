#include "WifiManager.h"
#include <WiFi.h>
#include <Preferences.h>
#include "mini/storage/logger.h"

// External helpers shared with BLEManager
// setStatus() and syncTimeWithNTP() are defined (non-static) in ble_manager.cpp.
// Declared extern here rather than duplicated, since duplicating status/NTP
// logic across two files is exactly how they'd quietly drift out of sync.
extern void setStatus(const char* status);
extern void syncTimeWithNTP();

static bool wifiConnectionInProgress = false;
static bool wifiManagerDone = false;

static unsigned long wifiConnectStartTime = 0;
static const unsigned long WIFI_TIMEOUT = 10000; // same timeout as BLEManager, kept consistent

bool hasStoredWifiCredentials() {
    Preferences prefs;

    if (!prefs.begin("wavelet", true)) { // read-only open
        Logger::error("WiFiManager", "NVS failed to open preferences");
        Serial.println("[NVS] Failed to open preferences");
        return false;
    }

    String ssid = prefs.getString("wifi_ssid", "");

    prefs.end();

    return !ssid.isEmpty();
}


void beginWifiManager() {

    Preferences prefs;

    if (!prefs.begin("wavelet", true)) {
        Logger::error("WiFiManager", "NVS failed to open preferences");
        Serial.println("[NVS] Failed to open preferences");
        setStatus("WIFI_FAILED");
        wifiManagerDone = true;
        return;
    }

    String ssid = prefs.getString("wifi_ssid", "");
    String pass = prefs.getString("wifi_pass", "");

    prefs.end();

    if (ssid.isEmpty()) {
        Serial.println("[WiFiManager] No stored SSID");
        setStatus("WIFI_FAILED");
        wifiManagerDone = true;
        return;
    }

    Serial.printf(
        "[WiFiManager] Starting connection to \"%s\"...\n",
        ssid.c_str()
    );

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    delay(100);

    WiFi.begin(
        ssid.c_str(),
        pass.c_str()
    );

    wifiConnectStartTime = millis();
    wifiConnectionInProgress = true;
    wifiManagerDone = false;

    setStatus("WIFI_CONNECTING");

    Serial.println("[WiFiManager] Connection started");
}

void processWifiManager() {

    if (!wifiConnectionInProgress) {
        return;
    }

    wl_status_t wifiStatus = WiFi.status();

    if (wifiStatus == WL_CONNECTED) {

        Serial.printf(
            "[WiFiManager] Connected! IP: %s\n",
            WiFi.localIP().toString().c_str()
        );

        wifiConnectionInProgress = false;
        wifiManagerDone = true;

        setStatus("WIFI_CONNECTED");

        syncTimeWithNTP();

        return;
    }

    if (millis() - wifiConnectStartTime >= WIFI_TIMEOUT) {

        Serial.println("[WiFiManager] Connection timeout");

        wifiConnectionInProgress = false;
        wifiManagerDone = true;

        setStatus("WIFI_FAILED");

        return;
    }
}

bool isWifiManagerDone() {
    return wifiManagerDone;
}