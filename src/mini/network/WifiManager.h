#pragma once

#include <Arduino.h>

// Returns true if valid WiFi credentials exist in NVS from a previous pairing.
bool hasStoredWifiCredentials();

// Starts a non-blocking WiFi connection attempt using stored NVS credentials.
// Call this once, then call processWifiManager() repeatedly from loop()/setup()
// until status resolves to WIFI_CONNECTED or WIFI_FAILED.
void beginWifiManager();

// Advances the connection state machine. Non-blocking — safe to call every loop.
void processWifiManager();

// True once processWifiManager() has reached a terminal state (connected or failed).
bool isWifiManagerDone();