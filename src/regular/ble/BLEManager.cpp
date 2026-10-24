#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Preferences.h>
#include <BluetoothA2DPSink.h>
extern BluetoothA2DPSink a2dp_sink;

// UUIDs
#define WAVELET_SERVICE_UUID    "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHAR_DEVICE_INFO_UUID   "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHAR_COMMAND_UUID       "beb5483e-36e1-4688-b7f5-ea07361b26a9"
#define CHAR_STATUS_UUID        "beb5483e-36e1-4688-b7f5-ea07361b26ac"
#define CHAR_DEVICE_NAME_UUID   "beb5483e-36e1-4688-b7f5-ea07361b26ad"

//Global Vars
extern Preferences prefs;
BLEServer*         pServer     = nullptr;
BLECharacteristic* pStatus     = nullptr;
BLECharacteristic* pDeviceInfo = nullptr;

bool deviceConnected = false;
// bool isSetupComplete = false;

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



void saveDeviceName(const String& name) {
    // Preferences prefs;

    // if (!prefs.begin("wavelet", false)) {
    //     Logger::error("BLE", "NVS failed to open preferences");
    //     Serial.println("[NVS] Failed to open preferences");
    //     return;
    // }

    prefs.putString("device_name", name);


    Serial.printf("[NVS] Device name saved: %s\n", name.c_str());
    // Logger::info("NVS", "Device name saved");

}

void saveSetupComplete() {
    prefs.putBool("setup_done", true);

    Serial.println("[NVS] Setup marked complete");

    Serial.printf(
        "[NVS] setup_done = %s\n",
        prefs.getBool("setup_done", false) ? "true" : "false"
    );
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

        //finish setup
        if (value == "SETUP_COMPLETE") {


            saveSetupComplete();

            // isSetupComplete = true;
            // prefs.putBool("setup_done", true);

            setStatus("READY");

            Serial.println(
                "[BLE] Setup complete — rebooting into normal mode"
            );

            delay(500);

            ESP.restart(); //restart device

            return;
        }

        if (value == "PLAY_PAUSE") {
            if (a2dp_sink.get_audio_state() == ESP_A2D_AUDIO_STATE_STARTED) a2dp_sink.pause();
            else a2dp_sink.play();
            setStatus("OK:PLAY_PAUSE");
        } else if (value.startsWith("SET_VOLUME:")) {
            int volume = value.substring(11).toInt();
            if (volume >= 0 && volume <= 100) {
                a2dp_sink.set_volume((volume * 127) / 100);
                setStatus("OK:VOLUME");
            } else setStatus("ERROR:VOLUME_RANGE");
        } else if (value == "GET_STATUS") {
            setStatus("{\"model\":\"regular\",\"capabilities\":[\"play_pause\",\"volume\"]}");
        } else if (value == "FACTORY_RESET:CONFIRM") {
            Preferences resetPrefs;
            resetPrefs.begin("wavelet", false);
            resetPrefs.clear();
            resetPrefs.end();
            resetPrefs.begin("volume", false);
            resetPrefs.clear();
            resetPrefs.end();
            setStatus("RESETTING"); delay(250); ESP.restart();
        } else if (value == "FACTORY_RESET") {
            setStatus("ERROR:CONFIRM_REQUIRED");
        } else {
            setStatus("ERROR:UNSUPPORTED_OR_UNKNOWN");
        }
        return;

        Serial.printf(
            "[BLE] Unknown command: %s\n",
            value.c_str()
        );
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
        "\",\"protocolVersion\":1,\"fw\":\"1.0.0\",\"capabilities\":[\"play_pause\",\"volume\",\"factory_reset\"]}";

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

    initBLE(
        deviceModel,
        deviceColor
    );
}

void processBleSetup() {}
