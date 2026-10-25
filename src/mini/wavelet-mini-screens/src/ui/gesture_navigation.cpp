#include "gesture_navigation.h"

#include <lvgl.h>

#include "screens.h"
#include "eez-flow.h"
#include "mini/rtc_manager/rtc_manager.h"

static void enable_gesture_bubbling(lv_obj_t *parent) {
    const uint32_t child_count = lv_obj_get_child_cnt(parent);
    for (uint32_t i = 0; i < child_count; ++i) {
        lv_obj_t *child = lv_obj_get_child(parent, i);
        lv_obj_add_flag(child, LV_OBJ_FLAG_GESTURE_BUBBLE);
        enable_gesture_bubbling(child);
    }
}

static ScreensEnum quickSettingsReturnScreen = SCREEN_ID_DEFAULT_CLOCK;
static bool alwaysOnReturnHandlerAdded = false;

static void alwaysOnTap(lv_event_t *event) {
    if (lv_event_get_code(event) == LV_EVENT_CLICKED) {
        eez_flow_set_screen(SCREEN_ID_DEFAULT_CLOCK, LV_SCR_LOAD_ANIM_FADE_IN, 180, 0);
    }
}

static ScreensEnum currentScreenId() {
    lv_obj_t *active = lv_scr_act();
    // if (active == objects.volume_pane) return SCREEN_ID_VOLUME_PANE;
    if (active == objects.media_pane) return SCREEN_ID_MEDIA_PANE;
    if (active == objects.quick_settings) return SCREEN_ID_QUICK_SETTINGS;
    if (active == objects.always_on_clock) return SCREEN_ID_ALWAYS_ON_CLOCK;
    return SCREEN_ID_DEFAULT_CLOCK;
}

static ScreensEnum currentPaneId(ScreensEnum current) {
    if (current == SCREEN_ID_QUICK_SETTINGS) return quickSettingsReturnScreen;
    if (current == SCREEN_ID_ALWAYS_ON_CLOCK) return SCREEN_ID_DEFAULT_CLOCK;
    // if (current == SCREEN_ID_VOLUME_PANE || current == SCREEN_ID_MEDIA_PANE) return current;
    return SCREEN_ID_DEFAULT_CLOCK;
}

static void navigateTo(ScreensEnum screen, lv_scr_load_anim_t animation) {
    if (currentScreenId() != screen) {
        eez_flow_set_screen(screen, animation, 180, 0);
    }
}

static void navigatePane(bool next) {
    const ScreensEnum pane = currentPaneId(currentScreenId());
    ScreensEnum destination = pane;

    // Three panes in order: Volume, Clock, Music. The ends are intentional;
    // swiping back from either end always returns to its neighboring pane.
    if (next) {
        // if (pane == SCREEN_ID_VOLUME_PANE) destination = SCREEN_ID_DEFAULT_CLOCK;
        if (pane == SCREEN_ID_DEFAULT_CLOCK) destination = SCREEN_ID_MEDIA_PANE;
    } else {
        if (pane == SCREEN_ID_MEDIA_PANE) destination = SCREEN_ID_DEFAULT_CLOCK;
        // else if (pane == SCREEN_ID_DEFAULT_CLOCK) destination = SCREEN_ID_VOLUME_PANE;
    }

    if (currentScreenId() == SCREEN_ID_QUICK_SETTINGS) {
        quickSettingsReturnScreen = destination;
    }
    navigateTo(destination, next ? LV_SCR_LOAD_ANIM_MOVE_RIGHT : LV_SCR_LOAD_ANIM_MOVE_LEFT);
}

static void screen_gesture_cb(lv_event_t *event) {
    if (lv_event_get_code(event) != LV_EVENT_GESTURE) {
        return;
    }

    lv_indev_t *input = lv_indev_get_act();
    if (!input) {
        return;
    }

    const ScreensEnum current = currentScreenId();

    switch (lv_indev_get_gesture_dir(input)) {
    case LV_DIR_TOP: // Swipe up enters Always On from the clock, or closes Quick Settings.
        if (current == SCREEN_ID_QUICK_SETTINGS) {
            navigateTo(quickSettingsReturnScreen, LV_SCR_LOAD_ANIM_MOVE_TOP);
        } else if (current == SCREEN_ID_DEFAULT_CLOCK) {
            navigateTo(SCREEN_ID_ALWAYS_ON_CLOCK, LV_SCR_LOAD_ANIM_MOVE_BOTTOM);
        }
        break;
    case LV_DIR_BOTTOM: // Swipe down opens Quick Settings from any screen.
        if (current != SCREEN_ID_QUICK_SETTINGS) {
            quickSettingsReturnScreen = current;
            navigateTo(SCREEN_ID_QUICK_SETTINGS, LV_SCR_LOAD_ANIM_MOVE_TOP);
        }
        break;
    case LV_DIR_LEFT:
        navigatePane(true);
        break;
    case LV_DIR_RIGHT:
        navigatePane(false);
        break;
    default:
        break;
    }
}

extern "C" void gesture_navigation_init(void) {
    lv_obj_t *screens[] = {
        objects.default_clock,
        // objects.volume_pane,
        objects.media_pane,
        objects.quick_settings,
        objects.always_on_clock,
    };

    for (lv_obj_t *screen : screens) {
        if (!screen) continue;
        lv_obj_add_flag(screen, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
        enable_gesture_bubbling(screen);
        lv_obj_add_event_cb(screen, screen_gesture_cb, LV_EVENT_GESTURE, NULL);
    }
    if (objects.always_on_clock && !alwaysOnReturnHandlerAdded) {
        lv_obj_add_event_cb(objects.always_on_clock, alwaysOnTap, LV_EVENT_CLICKED, NULL);
        alwaysOnReturnHandlerAdded = true;
    }
}

extern "C" void mini_clock_update(void) {
    static bool timezoneInitialized = false;
    static char lastHour[8] = "";
    static char lastMinute[8] = "";
    static char lastDay[16] = "";
    static char lastDate[16] = "";

    if (!timezoneInitialized) {
        RTC::begin("Africa/Lagos");
        timezoneInitialized = true;
    }

    if (!objects.default_clock) return;

    time_t now = time(nullptr);
    tm localTime;
    if (localtime_r(&now, &localTime) == nullptr) return;

    char hour[8], minute[8], day[16], date[16];
    strftime(hour, sizeof(hour), "%H", &localTime);
    strftime(minute, sizeof(minute), "%M", &localTime);
    strftime(day, sizeof(day), "%a", &localTime);
    strftime(date, sizeof(date), "%d %b", &localTime);

    // These are the current DefaultClock labels in the generated EEZ UI.
    // Check their types as well: EEZ can renumber objN handles after a UI edit.
    lv_obj_t *hourLabel = objects.obj20;
    lv_obj_t *minuteLabel = objects.obj21;
    lv_obj_t *dayLabel = objects.obj22;
    lv_obj_t *dateLabel = objects.obj23;
    if (objects.always_on_hour) lv_label_set_text(objects.always_on_hour, hour);
    if (objects.always_on_minute) lv_label_set_text(objects.always_on_minute, minute);
    if (objects.always_on_day) {
        char dayOfMonth[4];
        strftime(dayOfMonth, sizeof(dayOfMonth), "%d", &localTime);
        lv_label_set_text(objects.always_on_day, dayOfMonth);
    }

    // Enter the low detail clock after a minute without touch while on home.
    if (lv_scr_act() == objects.default_clock && lv_disp_get_inactive_time(NULL) >= 60000) {
        eez_flow_set_screen(SCREEN_ID_ALWAYS_ON_CLOCK, LV_SCR_LOAD_ANIM_FADE_IN, 220, 0);
    }

    if (strcmp(hour, lastHour) != 0) {
        if (hourLabel && lv_obj_check_type(hourLabel, &lv_label_class)) lv_label_set_text(hourLabel, hour);
        strcpy(lastHour, hour);
    }
    if (strcmp(minute, lastMinute) != 0) {
        if (minuteLabel && lv_obj_check_type(minuteLabel, &lv_label_class)) lv_label_set_text(minuteLabel, minute);
        strcpy(lastMinute, minute);
    }
    if (strcmp(day, lastDay) != 0) {
        if (dayLabel && lv_obj_check_type(dayLabel, &lv_label_class)) lv_label_set_text(dayLabel, day);
        strcpy(lastDay, day);
    }
    if (strcmp(date, lastDate) != 0) {
        if (dateLabel && lv_obj_check_type(dateLabel, &lv_label_class)) lv_label_set_text(dateLabel, date);
        strcpy(lastDate, date);
    }
}
