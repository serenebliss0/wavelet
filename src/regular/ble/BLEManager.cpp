#include "BLEManager.h"

#include <Arduino.h>

#define DEBUG
#define BATTERIES_CONNECTED

BLECharacteristic* batteryCharacteristic;

bool deviceConnected = false;
bool oldDeviceConnected = false;

//i haven't gotten some batteries yet. i'll test this part when i do : )
// but for now, here's a simple framework from what i've learnt
int readBatteryLevel() {
  int raw = analogRead(35); // ADC pin for battery
  float voltage = (raw / 4095.0) * 3.3 * 2; // adjust 2 if you have voltage divider
  int batteryPercent = (voltage / 4.2) * 100;
  if (batteryPercent > 100) batteryPercent = 100;
  return batteryPercent;
}

void update_battery() {

  #if !defined(BATTERIES_CONNECTED)
    return;
  #endif

  //null safety
  if (batteryCharacteristic == nullptr) {
    return;
  }

  static unsigned long lastBatteryUpdate = 0;
  if (millis() - lastBatteryUpdate > 2000) {

    int battery = readBatteryLevel();

    batteryCharacteristic->setValue((uint8_t*)&battery, sizeof(battery));
    batteryCharacteristic->notify();

    lastBatteryUpdate = millis();

#ifdef DEBUG
    Serial.print("Battery Level: ");
    Serial.print(battery);
    Serial.println("%");
#endif
  }
}

class MyServerCallbacks: public BLEServerCallbacks {

  void onConnect(BLEServer* pServer) {
      deviceConnected = true;

      #ifdef DEBUG
      Serial.println("Device connected");
      #endif
  }

  void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      #ifdef DEBUG
      Serial.println("Device disconnected");
      #endif
  }
};

void handleBLEConnection(BLEServer *pServer) {

  // If disconnected, restart advertising once
  if (!deviceConnected && oldDeviceConnected) {

      delay(500); // give stack time to settle
      pServer->startAdvertising();

      Serial.println("Restarting advertising");

      oldDeviceConnected = deviceConnected;
  }

  // If newly connected
  if (deviceConnected && !oldDeviceConnected) {
      oldDeviceConnected = deviceConnected;
  }
}