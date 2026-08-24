#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Preferences.h>
#include <WiFi.h>
#include "mini/storage/logger.h"

// UUIDs
#define WAVELET_SERVICE_UUID    "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHAR_DEVICE_INFO_UUID   "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHAR_COMMAND_UUID       "beb5483e-36e1-4688-b7f5-ea07361b26a9"
#define CHAR_WIFI_SSID_UUID     "beb5483e-36e1-4688-b7f5-ea07361b26aa"
#define CHAR_WIFI_PASS_UUID     "beb5483e-36e1-4688-b7f5-ea07361b26ab"
#define CHAR_STATUS_UUID        "beb5483e-36e1-4688-b7f5-ea07361b26ac"
#define CHAR_DEVICE_NAME_UUID   "beb5483e-36e1-4688-b7f5-ea07361b26ad"

//Global Vars
BLEServer*         pServer     = nullptr;
BLECharacteristic* pStatus     = nullptr;
BLECharacteristic* pDeviceInfo = nullptr;

bool deviceConnected = false;
bool isSetupComplete = false;

bool wifiConnectionRequested = false;
bool wifiConnectionInProgress = false;

unsigned long wifiConnectStartTime = 0;

const unsigned long WIFI_TIMEOUT = 10000;


String receivedSSID     = "";
String receivedPassword = "";
String receivedName     = "";

void setStatus(const char* status) {
    Serial.printf("[STATUS] %s\n", status);

    if (pStatus != nullptr) {
        pStatus->setValue(status);

        if (deviceConnected) {
            pStatus->notify();
        }
    }
}

void saveWifiCredentials(const String& ssid, const String& pass) {
    Preferences prefs;

    if (!prefs.begin("wavelet", false)) {
        Logger::error("BLE", "NVS failed to open preferences");
        Serial.println("[NVS] Failed to open preferences");
        return;
    }

    prefs.putString("wifi_ssid", ssid);
    prefs.putString("wifi_pass", pass);

    prefs.end();

    Serial.println("[NVS] WiFi credentials saved");
    Logger::info("BLE", "WiFi credentials saved");
}

void saveDeviceName(const String& name) {
    Preferences prefs;

    if (!prefs.begin("wavelet", false)) {
        Logger::error("BLE", "NVS failed to open preferences");
        Serial.println("[NVS] Failed to open preferences");
        return;
    }

    prefs.putString("device_name", name);

    prefs.end();

    Serial.printf("[NVS] Device name saved: %s\n", name.c_str());
    Logger::info("NVS", "Device name saved");

}

void saveSetupComplete() {
    Preferences prefs;

    if (!prefs.begin("wavelet", false)) {
        Logger::error("BLE", "NVS failed to open preferences");
        Serial.println("[NVS] Failed to open preferences");
        return;
    }

    prefs.putBool("setup_done", true);

    prefs.end();

    Serial.println("[NVS] Setup marked complete");
    Logger::info("NVS", "The device has completed setup");
}


void syncTimeWithNTP() {
    Serial.println("[TIME] Waiting for NTP sync...");
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

    time_t now = time(nullptr);
    unsigned long startMs = millis();
    const unsigned long NTP_TIMEOUT_MS = 10000; // give up after 10s so we don't hang forever

    while (now < 100000 && (millis() - startMs) < NTP_TIMEOUT_MS) {
        delay(200);
        now = time(nullptr);
    }

    if (now < 100000) {
        Serial.println("[TIME] NTP sync failed or timed out — SSL calls may fail");
        Logger::warning("Time", "NTP sync failed or timed out — SSL calls may fail");
    } else {
        Serial.println("[TIME] Synced!");
        Logger::info("Time", "Time synced with NTP successfully");
    }
}

    void startWifiConnection() {

        if (receivedSSID.isEmpty()) {
            Serial.println("[WiFi] Missing SSID");
            setStatus("WIFI_FAILED");
            return;
        }

        if (receivedPassword.isEmpty()) {
            Serial.println("[WiFi] Missing password");
            setStatus("WIFI_FAILED");
            return;
        }

        Serial.printf(
            "[WiFi] Starting connection to \"%s\"...\n",
            receivedSSID.c_str()
        );

        WiFi.mode(WIFI_STA);
        WiFi.disconnect();

        delay(100);

        WiFi.begin(
            receivedSSID.c_str(),
            receivedPassword.c_str()
        );

        wifiConnectStartTime = millis();
        wifiConnectionInProgress = true;

        setStatus("WIFI_CONNECTING");

        Serial.println("[WiFi] Connection started");
    }

    void processWifiConnection() {

        if (!wifiConnectionInProgress) {
            return;
        }
    
        wl_status_t wifiStatus = WiFi.status();
    
        if (wifiStatus == WL_CONNECTED) {
    
            Serial.printf(
                "[WiFi] Connected! IP: %s\n",
                WiFi.localIP().toString().c_str()
            );
    
            saveWifiCredentials(
                receivedSSID,
                receivedPassword
            );
    
            wifiConnectionInProgress = false;
    
            setStatus("WIFI_CONNECTED");

            //Sync time
            syncTimeWithNTP();
    
            return;
        }
    
        if (millis() - wifiConnectStartTime >= WIFI_TIMEOUT) {
    
            Serial.println(
                "[WiFi] Connection timeout"
            );
            Logger::warning("WiFi", "WiFi Connection timed out");
    
            wifiConnectionInProgress = false;
    
            setStatus("WIFI_FAILED");
    
            receivedSSID = "";
            receivedPassword = "";
    
            return;
        }
    }

//As usual, I don't understand anything from here : )
//Handles a bunch of BLE Callbacks
    class ServerCallbacks : public BLEServerCallbacks {

    void onConnect(BLEServer* pServer) override {

        deviceConnected = true;

        Serial.println("[BLE] Client connected");

        setStatus("IDLE");
    }

    void onDisconnect(BLEServer* pServer) override {

        deviceConnected = false;

        Serial.println(
            "[BLE] Client disconnected — restarting advertising"
        );

        BLEDevice::startAdvertising();
    }
};

class CommandCallback : public BLECharacteristicCallbacks {

    void onWrite(BLECharacteristic* pChar) override {

        String value = pChar->getValue().c_str();

        Serial.printf(
            "[BLE] Command: %s\n",
            value.c_str()
        );

        //Start wifi connection
        if (value == "SET_WIFI") {

            Serial.println(
                "[BLE] WiFi setup requested"
            );
        
            wifiConnectionRequested = true;
        
            return;
        }

        //finish setup
        if (value == "SETUP_COMPLETE") {

            if (WiFi.status() != WL_CONNECTED) {

                Serial.println(
                    "[BLE] Cannot complete setup — WiFi not connected"
                );
                Logger::warning("WiFi", "[BLE] Cannot complete setup — WiFi not connected");

                setStatus("WIFI_REQUIRED");
                return;
            }

            saveSetupComplete();

            isSetupComplete = true;

            setStatus("READY");

            Serial.println(
                "[BLE] Setup complete — rebooting into normal mode"
            );

            delay(500);

            ESP.restart(); //restart device

            return;
        }

        Serial.printf(
            "[BLE] Unknown command: %s\n",
            value.c_str()
        );
    }
};

class WifiSSIDCallback : public BLECharacteristicCallbacks {

    void onWrite(BLECharacteristic* pChar) override {

        receivedSSID = pChar->getValue().c_str();

        Serial.printf(
            "[BLE] SSID received: %s\n",
            receivedSSID.c_str()
        );
    }
};

class WifiPassCallback : public BLECharacteristicCallbacks {

    void onWrite(BLECharacteristic* pChar) override {

        receivedPassword = pChar->getValue().c_str();

        Serial.printf(
            "[BLE] Password received (length: %d)\n",
            receivedPassword.length()
        );

        // We do NOT connect here.
        // The Companion App must send:
        // SET_WIFI
        // after both SSID and password have been written.
    }
};

class DeviceNameCallback : public BLECharacteristicCallbacks {

    void onWrite(BLECharacteristic* pChar) override {

        receivedName = pChar->getValue().c_str();

        Serial.printf(
            "[BLE] Device name: %s\n",
            receivedName.c_str()
        );

        saveDeviceName(receivedName);
    }
};

void initBLE(String deviceModel, String deviceColor) {

    String advertisingName = "WVL-" + deviceModel;

    BLEDevice::init(
        advertisingName.c_str()
    );

    BLEDevice::setPower(
        ESP_PWR_LVL_P9
    );

    pServer = BLEDevice::createServer();

    pServer->setCallbacks(
        new ServerCallbacks()
    );

    BLEService* pService =
        pServer->createService(
            WAVELET_SERVICE_UUID
        );

    pDeviceInfo =
        pService->createCharacteristic(
            CHAR_DEVICE_INFO_UUID,
            BLECharacteristic::PROPERTY_READ
        );

    String info =
        "{\"model\":\"" +
        deviceModel +
        "\",\"color\":\"" +
        deviceColor +
        "\",\"fw\":\"1.0.0\"}";

    pDeviceInfo->setValue(
        info.c_str()
    );

    pStatus =
        pService->createCharacteristic(
            CHAR_STATUS_UUID,
            BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_NOTIFY
        );

    pStatus->addDescriptor(
        new BLE2902()
    );

    pStatus->setValue(
        "IDLE"
    );

    BLECharacteristic* pCommand =
        pService->createCharacteristic(
            CHAR_COMMAND_UUID,
            BLECharacteristic::PROPERTY_WRITE
        );

    pCommand->setCallbacks(
        new CommandCallback()
    );

    BLECharacteristic* pWifiSSID =
        pService->createCharacteristic(
            CHAR_WIFI_SSID_UUID,
            BLECharacteristic::PROPERTY_WRITE
        );

    pWifiSSID->setCallbacks(
        new WifiSSIDCallback()
    );

    BLECharacteristic* pWifiPass =
        pService->createCharacteristic(
            CHAR_WIFI_PASS_UUID,
            BLECharacteristic::PROPERTY_WRITE
        );

    pWifiPass->setCallbacks(
        new WifiPassCallback()
    );

    BLECharacteristic* pDeviceName =
        pService->createCharacteristic(
            CHAR_DEVICE_NAME_UUID,
            BLECharacteristic::PROPERTY_WRITE
        );

    pDeviceName->setCallbacks(
        new DeviceNameCallback()
    );

    //start service
    pService->start();

    BLEAdvertising* pAdvertising =
        BLEDevice::getAdvertising();

    pAdvertising->addServiceUUID(
        WAVELET_SERVICE_UUID
    );

    pAdvertising->setScanResponse(true);

    pAdvertising->setMinPreferred(0x06);
    pAdvertising->setMinPreferred(0x12);

    BLEDevice::startAdvertising();

    Serial.printf(
        "[BLE] Advertising as %s\n",
        advertisingName.c_str()
    );
}

//starts setup mode
void beginSetupMode(
    String deviceModel,
    String deviceColor
) {

    Serial.println(
        "[WAVELET] First boot — entering BLE setup mode"
    );
    Logger::info("System", "First boot — entering BLE setup mode");

    initBLE(
        deviceModel,
        deviceColor
    );
}

void processBleSetup() {

    if (wifiConnectionRequested) {

        wifiConnectionRequested = false;

        startWifiConnection();
    }

    processWifiConnection();
}