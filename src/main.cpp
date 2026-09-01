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
#include <WiFi.h>
#include "driver/i2s.h"
#include <Preferences.h>

#ifdef WAVELET_MINI
#include "mini/mini-setup-assistant.h"
#endif

#if defined(WAVELET_REGULAR)
#include "input/Buttons.h"
#include "audio/AudioManager.h"
#include "ble/BLEManager.h"
#include "core/Speaker.h"
#include "BluetoothA2DPSink.h"
#include "storage/PreferencesManager.h"
#endif


#ifdef WAVELET_MAX
#include "web/WebServer.h"
#include "wifi/WiFiManager.h"
#endif

Preferences prefs;

//Regular is quite cooked rn
#ifdef WAVELET_REGULAR
#include "Config.h"
AudioManager audio(prefs);
BluetoothA2DPSink a2dp_sink;
#endif

// comment this line to disable debug
#define DEBUG

//uncomment this line to enable BatteryStats
#define BATTERIES_CONNECTED

#define FIRMWARE_VERSION "1.0.0"

void setup() {

    #ifdef DEBUG
    Serial.begin(115200);
    #endif

    ledcSetup(0, 2000, 8);

    prefs.begin("app", false); // open once

    #if defined(WAVELET_REGULAR)
    pinMode(Config::BUZZER, OUTPUT);
    pinMode(Config::PWR_BUTTON, INPUT_PULLUP);
    pinMode(Config::MODE_BUTTON, INPUT_PULLUP);
    pinMode(Config::PREVIOUS_BUTTON, INPUT_PULLUP);
    pinMode(Config::NEXT_BUTTON, INPUT_PULLUP);
    pinMode(Config::PAUSE_BUTTON, INPUT_PULLUP);
    #endif

    #ifdef WAVELET_MINI
    initializeDisplay();
    startLED();
    initializePreferences();
    startOrCheckOnboarding();
    startFeatures();
    #endif

    #ifdef DEBUG
    String mac_addr = WiFi.macAddress();
    Serial.println(WiFi.macAddress());
    #endif

    #ifdef WAVELET_REGULAR
    i2s_pin_config_t my_pins = {
        .bck_io_num = 26,
        .ws_io_num = 25,
        .data_out_num = 4, //DIN
        .data_in_num = I2S_PIN_NO_CHANGE
    };

    a2dp_sink.set_pin_config(my_pins);
    a2dp_sink.set_on_connection_state_changed(on_connected);
    a2dp_sink.set_auto_reconnect(false);
    #endif

    #ifdef WAVELET_MAX
    getSongMetadata(); //achieve song info for the web ui
    #endif

    #ifdef WAVELET_REGULAR //update required
    a2dp_sink.start("Wavelet");
    #endif

    #ifdef WAVELET_MAX
    a2dp_sink.start("Wavelet Max");
    #endif

  
    // audio.play_startup_sound();

    // int rememberedVolume = readRememberedVolume();
    // a2dp_sink.set_volume(rememberedVolume);
    // //i2s_set_clk(I2S_NUM_0, 44100, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_STEREO);
    // audio.buzz(1000,1000);

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
    if (WiFi.status() == WL_CONNECTED) {
        updateSpotify();
    }
    #endif

#if defined(WAVELET_REGULAR)
#ifdef DEBUG
int battery_level = readBatteryLevel();
Serial.println(battery_level);
#endif
update_battery();
checkModeButton();
handlePowerButton();
handlePreviousButton();
handleNextButton();
#endif

}
