#include "mini_ui_controls.h"

#include <Arduino.h>
#include <Preferences.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <lvgl.h>

#include "mini/mini-ble/BLEManager.h"
#include "mini/battery/battery.h"
#include "mini/wavelet-mini-screens/src/ui/screens.h"
#include "mini/wavelet-mini-screens/src/ui/vars.h"
#include "mini/wavelet-mini-screens/src/ui/eez-flow.h"
#include "mini/audio/mini-audio-manager.h"
#include "mini/audio/volume_control.h"
#include "spotify_controller/Spotify.h"
#include "spotify_controller/album_art.h"

extern Preferences prefs;
extern bool deviceConnected;
void requestSpotifyStart();

namespace {
constexpr int kBrightnessChannel = 1;
constexpr int kDefaultBrightness = 80;
constexpr char kBrightnessKey[] = "mini_bright";
constexpr char kSpotifyEnabledKey[] = "spotify_enabled";
constexpr char kDndKey[] = "mini_dnd";
constexpr char kWifiEnabledKey[] = "mini_wifi_on";
constexpr char kBleEnabledKey[] = "mini_ble_on";
bool spotifyEnabled = true;
bool dndEnabled = false;
bool wifiEnabled = true;
bool bleEnabled = true;
uint32_t lastUiRefresh = 0;
bool wasWifiConnected = false;

void setChecked(lv_obj_t *button, bool checked) {
    if (!button) return;
    if (checked) lv_obj_add_state(button, LV_STATE_CHECKED);
    else lv_obj_clear_state(button, LV_STATE_CHECKED);
}

void brightnessChanged(lv_event_t *event) {
    lv_obj_t *slider = lv_event_get_target(event);
    const int value = constrain(lv_slider_get_value(slider), 0, 100);
    int duty = value * 255 / 100;
#if defined(TFT_BACKLIGHT_ON) && (TFT_BACKLIGHT_ON == LOW)
    duty = 255 - duty;
#endif
    ledcWrite(kBrightnessChannel, duty);
    if (lv_event_get_code(event) == LV_EVENT_RELEASED) prefs.putUChar(kBrightnessKey, value);
}

void wifiClicked(lv_event_t *event) {
    // LVGL has already toggled the checkable button before CLICKED is sent.
    // Treat checked as enabled so the visual state and the feature agree.
    wifiEnabled = lv_obj_has_state(lv_event_get_target(event), LV_STATE_CHECKED);
    prefs.putBool(kWifiEnabledKey, wifiEnabled);
    if (wifiEnabled) {
        String ssid = prefs.getString("wifi_ssid", "");
        String pass = prefs.getString("wifi_pass", "");
        if (!ssid.isEmpty()) {
            WiFi.mode(WIFI_STA);
            WiFi.begin(ssid.c_str(), pass.c_str());
        }
    } else {
        WiFi.disconnect(true, false);
        WiFi.mode(WIFI_OFF);
    }
}

void bleClicked(lv_event_t *event) {
    bleEnabled = lv_obj_has_state(lv_event_get_target(event), LV_STATE_CHECKED);
    prefs.putBool(kBleEnabledKey, bleEnabled);
    setBleControlEnabled(bleEnabled);
}

void spotifyClicked(lv_event_t *event) {
    spotifyEnabled = lv_obj_has_state(lv_event_get_target(event), LV_STATE_CHECKED);
    prefs.putBool(kSpotifyEnabledKey, spotifyEnabled);
    setSpotifyFeatureEnabled(spotifyEnabled);
    if (spotifyEnabled) requestSpotifyStart();
}

void dndClicked(lv_event_t *event) {
    dndEnabled = lv_obj_has_state(lv_event_get_target(event), LV_STATE_CHECKED);
    prefs.putBool(kDndKey, dndEnabled);
}

void playPauseClicked(lv_event_t *) { if (spotifyEnabled && WiFi.isConnected()) pauseCurrentlyPlaying(); }
void previousClicked(lv_event_t *) { if (spotifyEnabled && WiFi.isConnected()) playPreviousSong(); }
void nextClicked(lv_event_t *) { if (spotifyEnabled && WiFi.isConnected()) playNextSong(); }

void mediaSeek(lv_event_t *event) {
    if (lv_event_get_code(event) == LV_EVENT_RELEASED && spotifyEnabled && WiFi.isConnected()) {
        const int seconds = lv_slider_get_value(lv_event_get_target(event));
        seekToPosition(seconds * 1000);
    }
}

void applyBrightness(int value) {
    value = constrain(value, 0, 100);
    if (objects.brightness) {
        lv_slider_set_range(objects.brightness, 0, 100);
        lv_slider_set_value(objects.brightness, value, LV_ANIM_OFF);
    }
    int duty = value * 255 / 100;
#if defined(TFT_BACKLIGHT_ON) && (TFT_BACKLIGHT_ON == LOW)
    duty = 255 - duty;
#endif
    ledcWrite(kBrightnessChannel, duty);
}
}

bool miniSpotifyFeaturesEnabled() { return spotifyEnabled; }
bool miniDoNotDisturbEnabled() { return dndEnabled; }

void miniUiControlsInitialize() {
    spotifyEnabled = prefs.getBool(kSpotifyEnabledKey, true);
    dndEnabled = prefs.getBool(kDndKey, false);
    wifiEnabled = prefs.getBool(kWifiEnabledKey, true);
    bleEnabled = prefs.getBool(kBleEnabledKey, true);

    ledcSetup(kBrightnessChannel, 5000, 8);
#ifdef TFT_BL
    ledcAttachPin(TFT_BL, kBrightnessChannel);
#endif
    applyBrightness(prefs.getUChar(kBrightnessKey, kDefaultBrightness));

    if (objects.brightness) {
        lv_obj_add_event_cb(objects.brightness, brightnessChanged, LV_EVENT_VALUE_CHANGED, nullptr);
        lv_obj_add_event_cb(objects.brightness, brightnessChanged, LV_EVENT_RELEASED, nullptr);
    }
    if (objects.wifi_button) lv_obj_add_event_cb(objects.wifi_button, wifiClicked, LV_EVENT_CLICKED, nullptr);
    if (objects.bluetooth_button) lv_obj_add_event_cb(objects.bluetooth_button, bleClicked, LV_EVENT_CLICKED, nullptr);
    if (objects.spotify_button) lv_obj_add_event_cb(objects.spotify_button, spotifyClicked, LV_EVENT_CLICKED, nullptr);
    if (objects.dnd_button) lv_obj_add_event_cb(objects.dnd_button, dndClicked, LV_EVENT_CLICKED, nullptr);
    if (objects.play_pause) lv_obj_add_event_cb(objects.play_pause, playPauseClicked, LV_EVENT_CLICKED, nullptr);
    if (objects.previous_button) lv_obj_add_event_cb(objects.previous_button, previousClicked, LV_EVENT_CLICKED, nullptr);
    if (objects.next_button) lv_obj_add_event_cb(objects.next_button, nextClicked, LV_EVENT_CLICKED, nullptr);
    if (objects.media_bar) lv_obj_add_event_cb(objects.media_bar, mediaSeek, LV_EVENT_RELEASED, nullptr);

    setChecked(objects.wifi_button, wifiEnabled);
    setChecked(objects.bluetooth_button, bleEnabled);
    setChecked(objects.spotify_button, spotifyEnabled);
    setChecked(objects.dnd_button, dndEnabled);
    setSpotifyFeatureEnabled(spotifyEnabled);
}

void miniUiControlsUpdate() {
    albumArtProcessUi();
    const bool connected = WiFi.status() == WL_CONNECTED;
    if (connected && !wasWifiConnected) configTzTime("WAT-1", "pool.ntp.org", "time.nist.gov");
    wasWifiConnected = connected;
    if (millis() - lastUiRefresh < 1000) return;
    lastUiRefresh = millis();

    const uint8_t battery = Battery::percentage();
    const char *icon = battery >= 80 ? LV_SYMBOL_BATTERY_FULL :
        battery >= 60 ? LV_SYMBOL_BATTERY_3 : battery >= 40 ? LV_SYMBOL_BATTERY_2 :
        battery >= 20 ? LV_SYMBOL_BATTERY_1 : LV_SYMBOL_BATTERY_EMPTY;
    eez::flow::setGlobalVariable(FLOW_GLOBAL_VARIABLE_BATTERY_PERCENTAGE, eez::Value((int)battery));
    eez::flow::setGlobalVariable(FLOW_GLOBAL_VARIABLE_BATTERY_ICON, eez::Value(icon));
    eez::flow::setGlobalVariable(FLOW_GLOBAL_VARIABLE_IS_WIFI_CONNECTED, eez::Value(connected));

    //removed unnecessary change
    // if (objects.wifi_status) lv_label_set_text(objects.wifi_status, connected ? "Connected" : "Disconnected");

    if (objects.media_bar && spotifyEnabled) updateSpotifyMediaUi();
}

bool shuffleEnabled = false;

void toggleShuffle() {
    if (shuffleEnabled) {
        disableShuffle();
        shuffleEnabled = false;
    } else {
        enableShuffle();
        shuffleEnabled = true;
    }
}


enum RepeatMode {
    REPEAT_OFF,
    REPEAT_ALL,
    REPEAT_ONE
};

RepeatMode repeatMode = REPEAT_OFF;

void toggleRepeat() {
    switch (repeatMode) {
        case REPEAT_OFF:
            setRepeatOff();
            repeatMode = REPEAT_ALL;
            break;

        case REPEAT_ALL:
            setRepeatTrack();
            repeatMode = REPEAT_ONE;
            break;

        case REPEAT_ONE:
            setRepeatContext();
            repeatMode = REPEAT_OFF;
            break;
    }
}


extern "C" void action_on_click_shuffle(lv_event_t *e) {
    // TODO: Implement action on_click_shuffle here
    toggleShuffle(); //make it sync with spotify
}

extern "C" void action_on_click_repeat(lv_event_t *e) {
    toggleRepeat(); //make this also sync with spotify
}

void updateAboutPage(){
    lv_label_set_text(
        objects.ip_address,
        (WiFi.localIP()).toString().c_str()
    );
    
    lv_label_set_text(
        objects.wifi_mac_address,
        WiFi.macAddress().c_str()
    );

    lv_label_set_text(
        objects.uptime_duration,
        static_cast <String>(millis()).c_str()
    );

    //Set to device name for now
    lv_label_set_text(
        objects.bluetooth_address,
        prefs.getString("device_name").c_str()
    );
}