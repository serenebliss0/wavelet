#pragma once

#ifdef WAVELET_MINI
#include "spotify_controller/Spotify.h"
#include "mini/qr/qr_setup.h"
#include "mini/battery/battery.h"
#include "mini/MiniConfig.h"
#include "mini/neopixel/NeoPixel.h"
#include "mini/rtc_manager/rtc_manager.h"
#include "mini/storage/logger.h"
#include "mini/storage/Paths.h"
#include "mini/storage/sd_manager.h"
#include "mini/storage/settings.h"
#include "mini/mini-ble/BLEManager.h"
#include "mini/wavelet-mini-screens/src/ui/screens.h"
#include "mini/wavelet-mini-screens/src/ui/ui.h"
#include <TFT_eSPI.h>
#include "mini/setup_helper.h"
#include "mini/display/touch.h"
#include "mini/network/WifiManager.h"
#include "mini/audio/mini-audio-manager.h"
#endif

void initializeDisplay();
void startLED();
void initializePreferences();
void startOrCheckOnboarding();
void initializeSD();
void initializeWiFi();
void startSpotify();
void startFeatures();