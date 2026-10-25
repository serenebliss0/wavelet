#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_QUICK_SETTINGS = 1,
    SCREEN_ID_BOOT_SPLASH = 2,
    SCREEN_ID_INITIAL_QR_PAGE = 3,
    SCREEN_ID_ONBOARDING1 = 4,
    SCREEN_ID_ONBOARDING2 = 5,
    SCREEN_ID_ONBOARDING3 = 6,
    SCREEN_ID_DEFAULT_CLOCK = 7,
    SCREEN_ID_MEDIA_PANE = 8,
    SCREEN_ID_ALWAYS_ON_CLOCK = 9,
    SCREEN_ID_SETTINGS_PAGE = 10,
    _SCREEN_ID_LAST = 10
};

typedef struct _objects_t {
    lv_obj_t *quick_settings;
    lv_obj_t *boot_splash;
    lv_obj_t *initial_qr_page;
    lv_obj_t *onboarding1;
    lv_obj_t *onboarding2;
    lv_obj_t *onboarding3;
    lv_obj_t *default_clock;
    lv_obj_t *media_pane;
    lv_obj_t *always_on_clock;
    lv_obj_t *settings_page;
    lv_obj_t *wifi_button;
    lv_obj_t *bluetooth_button;
    lv_obj_t *spotify_button;
    lv_obj_t *dnd_button;
    lv_obj_t *brightness;
    lv_obj_t *volume_slider;
    lv_obj_t *gesture_hint_quick_settings;
    lv_obj_t *open_settings;
    lv_obj_t *obj0;
    lv_obj_t *power_button;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *wavelet_log;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *obj10;
    lv_obj_t *obj11;
    lv_obj_t *obj12;
    lv_obj_t *obj13;
    lv_obj_t *obj14;
    lv_obj_t *obj15;
    lv_obj_t *obj16;
    lv_obj_t *obj17;
    lv_obj_t *obj18;
    lv_obj_t *obj19;
    lv_obj_t *obj20;
    lv_obj_t *obj21;
    lv_obj_t *obj22;
    lv_obj_t *obj23;
    lv_obj_t *wifi_status;
    lv_obj_t *obj24;
    lv_obj_t *obj25;
    lv_obj_t *obj26;
    lv_obj_t *obj27;
    lv_obj_t *obj28;
    lv_obj_t *currently_playing;
    lv_obj_t *battery_icon;
    lv_obj_t *battery_percentage;
    lv_obj_t *wallpaper_image;
    lv_obj_t *obj29;
    lv_obj_t *obj30;
    lv_obj_t *obj31;
    lv_obj_t *obj32;
    lv_obj_t *album_cover;
    lv_obj_t *play_pause;
    lv_obj_t *obj33;
    lv_obj_t *previous_button;
    lv_obj_t *next_button;
    lv_obj_t *song_title;
    lv_obj_t *artist_name;
    lv_obj_t *media_bar;
    lv_obj_t *obj34;
    lv_obj_t *obj35;
    lv_obj_t *obj36;
    lv_obj_t *obj37;
    lv_obj_t *obj38;
    lv_obj_t *obj39;
    lv_obj_t *obj40;
    lv_obj_t *obj41;
    lv_obj_t *always_on_hour;
    lv_obj_t *always_on_minute;
    lv_obj_t *always_on_day;
    lv_obj_t *obj42;
    lv_obj_t *settings_back_button;
    lv_obj_t *obj43;
    lv_obj_t *obj44;
} objects_t;

extern objects_t objects;

void create_screen_quick_settings();
void tick_screen_quick_settings();

void create_screen_boot_splash();
void tick_screen_boot_splash();

void create_screen_initial_qr_page();
void tick_screen_initial_qr_page();

void create_screen_onboarding1();
void tick_screen_onboarding1();

void create_screen_onboarding2();
void tick_screen_onboarding2();

void create_screen_onboarding3();
void tick_screen_onboarding3();

void create_screen_default_clock();
void tick_screen_default_clock();

void create_screen_media_pane();
void tick_screen_media_pane();

void create_screen_always_on_clock();
void tick_screen_always_on_clock();

void create_screen_settings_page();
void tick_screen_settings_page();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

// Color themes

enum Themes {
    THEME_ID_DARK_MODE,
    THEME_ID_LIGHT_MODE,
};
enum Colors {
    COLOR_ID_BACKGROUND,
    COLOR_ID_SURFACE,
    COLOR_ID_SURFACE_VARIANT,
    COLOR_ID_BORDER,
    COLOR_ID_INACTIVE,
    COLOR_ID_PRIMARY_TEXT,
    COLOR_ID_SECONDARY_TEXT,
    COLOR_ID_DIM_TEXT,
    COLOR_ID_SPOTIFY_GREEN,
    COLOR_ID_SUCCESS,
    COLOR_ID_WARNING,
    COLOR_ID_ERROR,
    COLOR_ID_WHITE,
    COLOR_ID_PRIMARY_BUTTON,
    COLOR_ID_PRIMARY_BUTTON_TEXT,
    COLOR_ID_SECONDARY_BUTTON,
    COLOR_ID_SECONDARY_BUTTON_TEXT,
    COLOR_ID_DISABLED_BUTTON,
    COLOR_ID_DISABLED_BUTTON_TEXT,
    COLOR_ID_DESTRUCTIVE_BUTTON,
    COLOR_ID_DESTRUCTIVE_BUTTON_TEXT,
};
void change_color_theme(uint32_t themeIndex);
extern uint32_t theme_colors[2][21];

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/