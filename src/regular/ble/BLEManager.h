#pragma once

#include <BLEDevice.h>

#define BATTERY_SERVICE_UUID        "180F" // standard battery service
#define BATTERY_CHAR_UUID           "2A19" // standard battery level

extern BLECharacteristic* batteryCharacteristic;

int readBatteryLevel();
void update_battery();
