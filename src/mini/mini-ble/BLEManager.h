#pragma once

#include <Arduino.h>
#include <BLEDevice.h>

#define WAVELET_SERVICE_UUID    "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHAR_DEVICE_INFO_UUID   "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHAR_COMMAND_UUID       "beb5483e-36e1-4688-b7f5-ea07361b26a9"
#define CHAR_WIFI_SSID_UUID     "beb5483e-36e1-4688-b7f5-ea07361b26aa"
#define CHAR_WIFI_PASS_UUID     "beb5483e-36e1-4688-b7f5-ea07361b26ab"
#define CHAR_STATUS_UUID        "beb5483e-36e1-4688-b7f5-ea07361b26ac"
#define CHAR_DEVICE_NAME_UUID   "beb5483e-36e1-4688-b7f5-ea07361b26ad"

extern bool deviceConnected;
extern bool isSetupComplete;


/**
 * Initializes the BLE setup service and begins advertising.
 *
 * @param deviceModel Model identifier (e.g. "mini")
 * @param deviceColor Device colour (e.g. "strawberry_pink")
 */
void initBLE(String deviceModel, String deviceColor);

/**
 * Enters Wavelet setup mode.
 * Called when the device has not yet been provisioned.
 *
 * @param deviceModel Model identifier
 * @param deviceColor Device colour
 */
void beginSetupMode(String deviceModel, String deviceColor);

/**
 * Attempts to connect using the currently received credentials.
 */
void attemptWifiConnection();

void saveWifiCredentials(String ssid, String pass);
void saveDeviceName(String name);
void saveSetupComplete();

void processBleSetup();