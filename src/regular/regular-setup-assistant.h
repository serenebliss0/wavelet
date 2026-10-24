#pragma once

#include "regular/input/Buttons.h"
#include "regular/audio/AudioManager.h"
#include "regular/ble/BLEManager.h"
#include "regular/core/Speaker.h"
#include "BluetoothA2DPSink.h"
#include "regular/storage/PreferencesManager.h"
#include "Config.h" //Pin outs, etc...

void initializeGPIO();
void initializeI2S();
void startA2DP();
void playDebugBeep();
void handleButtons();
void playStartupSound();
void startOrCheckOnboarding();