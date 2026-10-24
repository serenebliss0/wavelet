#include "volume_control.h"

#include <Preferences.h>
#include <lvgl.h>

#include "mini/audio/mini-audio-manager.h"
#include "mini/wavelet-mini-screens/src/ui/screens.h"
#include "mini/wavelet-mini-screens/src/ui/eez-flow.h"
#include "mini/wavelet-mini-screens/src/ui/vars.h"

extern Preferences prefs;

namespace {
constexpr uint8_t kDefaultVolumePercent = 67;
constexpr int kCodecMinVolume = 70;
constexpr int kCodecMaxVolume = 80;
constexpr char kVolumePreferenceKey[] = "mini_volume";

int codecVolumeForPercent(uint8_t percent)
{
    return kCodecMinVolume +
        ((percent * (kCodecMaxVolume - kCodecMinVolume) + 50) / 100);
}

void updateVolumeUi()
{
    if (objects.volume_slider &&
        lv_slider_get_value(objects.volume_slider) != miniVolumeGetPercent()) {
        lv_slider_set_value(objects.volume_slider, miniVolumeGetPercent(), LV_ANIM_OFF);
    }

    if (objects.obj21) {
        char text[5];
        snprintf(text, sizeof(text), "%u%%", miniVolumeGetPercent());
        lv_label_set_text(objects.obj21, text);
    }
}

void volumeSliderEvent(lv_event_t *event)
{
    const lv_event_code_t code = lv_event_get_code(event);
    lv_obj_t *slider = lv_event_get_target(event);

    if (code == LV_EVENT_VALUE_CHANGED) {
        const int value = lv_slider_get_value(slider);
        if (value >= 0 && value <= 100) {
            miniVolumeSetPercent(static_cast<uint8_t>(value), false);
        }
    } else if (code == LV_EVENT_RELEASED) {
        prefs.putUChar(kVolumePreferenceKey, miniVolumeGetPercent());
    }
}
}

void miniVolumeInitialize()
{
    const uint8_t saved = prefs.getUChar(kVolumePreferenceKey, kDefaultVolumePercent);
    const uint8_t initial = saved <= 100 ? saved : kDefaultVolumePercent;
    eez::flow::setGlobalVariable(FLOW_GLOBAL_VARIABLE_VOLUME_LEVEL, eez::Value(initial));
}

uint8_t miniVolumeGetPercent()
{
    const int value = eez::flow::getGlobalVariable(FLOW_GLOBAL_VARIABLE_VOLUME_LEVEL).getInt();
    return value >= 0 && value <= 100 ? static_cast<uint8_t>(value) : kDefaultVolumePercent;
}

int miniVolumeCodecLevel()
{
    return codecVolumeForPercent(miniVolumeGetPercent());
}

void miniVolumeSetPercent(uint8_t percent, bool persist)
{
    if (percent > 100) return;

    eez::flow::setGlobalVariable(FLOW_GLOBAL_VARIABLE_VOLUME_LEVEL, eez::Value(percent));
    AudioManager::setVolume(miniVolumeCodecLevel());
    if (persist) {
        prefs.putUChar(kVolumePreferenceKey, miniVolumeGetPercent());
    }
    updateVolumeUi();
}

void miniVolumeBindUi()
{
    if (objects.volume_slider) {
        lv_slider_set_range(objects.volume_slider, 0, 100);
        lv_obj_add_event_cb(
            objects.volume_slider,
            volumeSliderEvent,
            LV_EVENT_VALUE_CHANGED,
            nullptr
        );
        lv_obj_add_event_cb(
            objects.volume_slider,
            volumeSliderEvent,
            LV_EVENT_RELEASED,
            nullptr
        );
    }
    updateVolumeUi();
}
