#pragma once
#include <Arduino.h>
#include <Preferences.h>
#include <lvgl.h>
#include "mini/storage/logger.h"


#pragma once

String getOrCreateSetupToken();
String buildQRPayload(String deviceId, String color);
bool generateQR(const char* payload, uint8_t* qrcode, uint8_t* temp);
void printQRToSerial(const String& payload);
void showSetupQR(String ssid, String password, lv_obj_t* parent);