/*
 * Project Name: Wavelet
 * Description: A family of ESP32-based smart speakers built from a single shared codebase.
 * Author: Semire Ajayi
 * Date: 12-MAR-2026
 * 
 * Hardware:
 * 
 * (Mini)
 * - 1x 2.8inch ESP32-S3 Display Module
 * - 2x 18650 Lithium Batteries
 * - 1x 4ohm, 8-Watt Speaker 
 * - 1x Passive Buzzer
 * - 1x Light Dependent Resistor (LDR)
 * - 3x Push Buttons
 * 
 * (Regular)
 * - 1x ESP32 DevKit V1
 * - 1x MAX98357A I2S Amplifier
 * - 1x 4ohm, 8-Watt Speaker 
 * - 1x Passive Buzzer
 * - 2x 18650 Lithium Batteries
 * - 1x TP4056 Charging Module
 * - 1x 5k-ohm Potentiometer
 * - 4x Push Buttons
 * 
 * Connections:
 * (See Config.h for wavelet regular, MiniConfig for wavelet mini)
 * 
 */

#include <Arduino.h>
// #include <WiFi.h>
#include "driver/i2s.h"
#include <Preferences.h>

#ifdef WAVELET_MINI
#include "mini/mini-setup-assistant.h" //contains functionality for the wavelet mini
#endif

#ifdef WAVELET_REGULAR
#include "regular/regular-setup-assistant.h" //contains functionality for the wavelet regular
#endif

#ifdef WAVELET_MAX
#include "web/WebServer.h"
#include "wifi/WiFiManager.h"
#endif

Preferences prefs; //Global preferences object

// comment this line to disable debug
#define DEBUG

#define MINI_FIRMWARE_VERSION "0.5.1"
#define REGULAR_FIRMWARE_VERSION "0.1.0"
#define MAX_FIRMWARE_VERSION "0.0.0"

void setup() {

    #ifdef DEBUG
    Serial.begin(115200);
    #endif

    ledcSetup(0, 2000, 8);

    // prefs.begin("app", false); // open once
    prefs.begin("wavelet", false);

    #ifdef WAVELET_MINI
    initializeDisplay();
    startLED();
    initializePreferences();
    startOrCheckOnboarding();
    startFeatures();
    #endif

    #ifdef WAVELET_REGULAR

    initializeGPIO();
    initializeI2S();
    startA2DP();
    startOrCheckOnboarding();

    #ifdef DEBUG
    playDebugBeep();
    #endif

    // playStartupSound();
    #endif

    #ifdef WAVELET_MAX
    getSongMetadata(); //achieve song info for the web ui
    a2dp_sink.start("Wavelet Max");
    #endif


    // int rememberedVolume = readRememberedVolume();
    // a2dp_sink.set_volume(rememberedVolume);
    // //i2s_set_clk(I2S_NUM_0, 44100, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_STEREO);

    #ifdef WAVELET_MAX
    connectWiFi();
    delay(5000);
    startWebServer();
    getSongMetadata();
    #endif
}

void loop() {

    //mini
    #ifdef WAVELET_MINI
    //LVGL events
    lv_timer_handler();
    ui_tick();

    //Neopixel LED handler
    ledUpdate();

    //WiFi
    processBleSetup();

    //Spotify
        // updateSpotify();
        handleSpotifyLoop();
    #endif

    #ifdef WAVELET_REGULAR
    handleButtons();
    processBleSetup();
    #endif

}
