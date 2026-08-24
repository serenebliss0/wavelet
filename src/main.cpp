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

#ifdef WAVELET_MINI
#include "spotify_controller/Spotify.h"
#include "mini/qr_setup.h"
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
#endif


Preferences prefs;

//Setting up display for MINI
// TODO: Give each model its own module and free up main.cpp
#ifdef WAVELET_MINI
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 240;
static lv_disp_draw_buf_t disp_buf;
static lv_color_t buf[screenWidth * 30];
#endif

#ifdef WAVELET_MINI
TFT_eSPI my_lcd = TFT_eSPI();

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    my_lcd.setAddrWindow(area->x1, area->y1, w, h);
    my_lcd.pushColors((uint16_t *)&color_p->full, w * h, true);
    lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
    if (touch_touched()) {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = touch_last_x;
        data->point.y = touch_last_y;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}
#endif


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

    //wavelet mini setup proc
    #ifdef WAVELET_MINI

    //TODO: move to display init module
    my_lcd.init();
    my_lcd.fillScreen(0x0000); //Black by default
    my_lcd.setRotation(1);
    
    touch_init(my_lcd.width(), my_lcd.height(), my_lcd.getRotation());
    
    lv_init();
    delay(10);
    
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, screenWidth * 30);
    
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = my_lcd.width();
    disp_drv.ver_res = my_lcd.height();
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &disp_buf;
    lv_disp_drv_register(&disp_drv);
    
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    //Start LED
    ledInit();

    //Change led state to boot
    ledSetState(LedState::BOOT);

    //NVS for mini
    Preferences prefs;
    prefs.begin("wavelet", true);
    bool setupDone = prefs.getBool("setup_done", false);
    prefs.end();

    String payload = "";
    String token = getOrCreateSetupToken();

    // //debug only, negate logic in prod
    if (!setupDone) {
        //Change later
        //Color picker later
        beginSetupMode("mini", "strawberry_pink");
        payload = getSetupPayload();
        #ifdef DEBUG
        printQRToSerial(payload);
        #endif
    }


    //init LVGL UI and create screens
    ui_init();
    create_screens();

    //change the qrcode to the generated payload
    lv_qrcode_update(
        objects.obj0,
        payload.c_str(),
        payload.length()
    );
    //change the manual code to the token
    lv_label_set_text(
        objects.obj6,
        token.c_str()
    );

    //Init filesystem
    SDManager::begin();

    //Gate features requiring wifi
    if (hasStoredWifiCredentials()) {
        beginWifiManager();
        while (!isWifiManagerDone()) {
            processWifiManager();
            delay(10);
        }
        if (WiFi.status() == WL_CONNECTED) {
            initializeSpotify();
            authenticateSpotify();
        }
    }
    #endif //end of mini setup


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
