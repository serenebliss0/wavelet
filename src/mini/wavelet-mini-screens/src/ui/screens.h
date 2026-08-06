#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_BOOT_SPLASH = 1,
    SCREEN_ID_INITIAL_QR_PAGE = 2,
    SCREEN_ID_ONBOARDING1 = 3,
    SCREEN_ID_ONBOARDING2 = 4,
    SCREEN_ID_ONBOARDING3 = 5,
    SCREEN_ID_DEFAULT_CLOCK = 6,
    _SCREEN_ID_LAST = 6
};

typedef struct _objects_t {
    lv_obj_t *boot_splash;
    lv_obj_t *initial_qr_page;
    lv_obj_t *onboarding1;
    lv_obj_t *onboarding2;
    lv_obj_t *onboarding3;
    lv_obj_t *default_clock;
    lv_obj_t *wavelet_log;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
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
} objects_t;

extern objects_t objects;

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
};
void change_color_theme(uint32_t themeIndex);
extern uint32_t theme_colors[2][13];

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/