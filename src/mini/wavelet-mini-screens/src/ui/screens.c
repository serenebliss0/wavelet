#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;

static const char *screen_names[] = { "BootSplash", "InitialQRPage", "Onboarding1", "Onboarding2", "Onboarding3", "DefaultClock", "QuickSettings", "MediaPane", "AlwaysOnClock", "SettingsPage", "Settings_Connectivity", "About Wavelet_1", "About Wavelet_2", "About Wavelet_3", "SecretPage" };
static const char *object_names[] = { "boot_splash", "initial_qr_page", "onboarding1", "onboarding2", "onboarding3", "default_clock", "quick_settings", "media_pane", "always_on_clock", "settings_page", "settings_connectivity", "about_wavelet_1", "about_wavelet_2", "about_wavelet_3", "secret_page", "wavelet_log", "qr_token", "obj0", "obj1", "obj2", "obj3", "obj4", "generated_token_label", "obj5", "obj6", "obj7", "obj8", "obj9", "obj10", "obj11", "obj12", "obj13", "obj14", "obj15", "obj16", "volume_icon", "volume_level", "wifi_status", "hour_default_clock", "minute_default_clock", "day_default_clock", "date_default_clock", "obj17", "currently_playing", "battery_icon", "battery_percentage", "wallpaper_image", "wifi_button", "bluetooth_button", "spotify_button", "dnd_button", "brightness", "volume_slider", "gesture_hint_quick_settings", "open_settings", "obj18", "power_button", "obj19", "obj20", "obj21", "hidden_home_btn", "obj22", "obj23", "spotify_volume_icon", "spotify_volume_label", "album_cover", "play_pause", "obj24", "previous_button", "next_button", "song_title", "artist_name", "media_bar", "obj25", "obj26", "shuffle_button", "obj27", "loop_button", "obj28", "playing_on", "obj29", "obj30", "obj31", "always_on_hour", "always_on_minute", "always_on_day", "obj32", "obj33", "obj34", "settings_back_button", "obj35", "obj36", "obj37", "obj38", "obj39", "obj40", "obj41", "obj42", "obj43", "obj44", "obj45", "obj46", "obj47", "obj48", "obj49", "obj50", "obj51", "obj52", "obj53", "settings_about_device", "obj54", "obj55", "obj56", "wavelet_log_1", "settings_back_button_1", "obj57", "model_number", "obj58", "serial_number", "obj59", "uptime_duration", "obj60", "settings_back_button_4", "obj61", "wavelet_log_2", "settings_back_button_2", "obj62", "ip_address", "obj63", "wifi_mac_address", "obj64", "bluetooth_address", "obj65", "settings_back_button_5", "obj66", "settings_back_button_6", "obj67", "wavelet_log_3", "settings_back_button_3", "obj68", "settings_back_button_7", "obj69", "obj70", "obj71", "obj72", "obj73", "obj74", "obj75", "obj76", "obj77", "obj78" };

//
// Event handlers
//

lv_obj_t *tick_value_change_obj;

static void event_handler_cb_onboarding1_obj6(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 4, 0, e);
    }
}

static void event_handler_cb_onboarding2_obj10(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 4, 0, e);
    }
}

static void event_handler_cb_onboarding3_obj14(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 4, 0, e);
    }
}

static void event_handler_cb_default_clock_obj17(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 9, 0, e);
    }
}

static void event_handler_cb_quick_settings_open_settings(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 12, 0, e);
    }
}

static void event_handler_cb_quick_settings_hidden_home_btn(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 18, 0, e);
    }
}

static void event_handler_cb_media_pane_play_pause(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 5, 0, e);
    }
}

static void event_handler_cb_media_pane_shuffle_button(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_on_click_shuffle(e);
    }
}

static void event_handler_cb_media_pane_loop_button(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_on_click_repeat(e);
    }
}

static void event_handler_cb_settings_page_settings_back_button(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 3, 0, e);
    }
}

static void event_handler_cb_settings_page_obj36(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 5, 0, e);
    }
}

static void event_handler_cb_settings_page_obj39(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 8, 0, e);
    }
}

static void event_handler_cb_settings_page_obj42(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 11, 0, e);
    }
}

static void event_handler_cb_settings_page_obj45(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 14, 0, e);
    }
}

static void event_handler_cb_settings_page_obj48(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 17, 0, e);
    }
}

static void event_handler_cb_settings_page_obj51(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 20, 0, e);
    }
}

static void event_handler_cb_settings_page_settings_about_device(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 23, 0, e);
    }
}

static void event_handler_cb_about_wavelet_1_settings_back_button_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 2, 0, e);
    }
}

static void event_handler_cb_about_wavelet_1_settings_back_button_4(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 11, 0, e);
    }
}

static void event_handler_cb_about_wavelet_2_settings_back_button_2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 2, 0, e);
    }
}

static void event_handler_cb_about_wavelet_2_settings_back_button_5(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 11, 0, e);
    }
}

static void event_handler_cb_about_wavelet_2_settings_back_button_6(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 13, 0, e);
    }
}

static void event_handler_cb_about_wavelet_3_wavelet_log_3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 0, 0, e);
    }
}

static void event_handler_cb_about_wavelet_3_settings_back_button_3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 2, 0, e);
    }
}

static void event_handler_cb_about_wavelet_3_settings_back_button_7(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 6, 0, e);
    }
}

//
// Screens
//

void create_screen_boot_splash() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.boot_splash = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SNAPPABLE|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // wavelet_log
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.wavelet_log = obj;
            lv_obj_set_pos(obj, 91, 96);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_wavelet_logo);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_boot_splash();
}

void tick_screen_boot_splash() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
}

void create_screen_initial_qr_page() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.initial_qr_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // qrToken
            lv_obj_t *obj = lv_qrcode_create(parent_obj, 96, lv_color_hex(0x000000), lv_color_hex(0xffffff));
            objects.qr_token = obj;
            lv_obj_set_pos(obj, 10, 72);
            lv_obj_set_size(obj, 96, 96);
            lv_qrcode_update(obj, "{generatedPayloadToken}", 23);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_border_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_opa(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(0xff9d9d), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 127, 72);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_nunito_18_bold, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Connect to Wavelet");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 127, 98);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 45);
            lv_obj_set_style_width(obj, 163, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_inter_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Open the Wavelet app on your phone and scan the QR code, or enter the code below.");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 127, 143);
            lv_obj_set_size(obj, 163, 57);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_lighten(lv_color_hex(0x4f762e), 0), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xccccff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 127, 143);
            lv_obj_set_size(obj, 163, 57);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xf04f76), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xf04f76), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj4 = obj;
            lv_obj_set_pos(obj, 135, 150);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_inter_7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "MANUAL CODE");
        }
        {
            // generatedTokenLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.generated_token_label = obj;
            lv_obj_set_pos(obj, 135, 165);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
    }
    
    tick_screen_initial_qr_page();
}

void tick_screen_initial_qr_page() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 7, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.generated_token_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.generated_token_label;
            lv_label_set_text(objects.generated_token_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_onboarding1() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.onboarding1 = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj5 = obj;
            lv_obj_set_pos(obj, 11, 21);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_nunito_18_bold, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Quick Settings");
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 11, 71);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_onboarding_tutorial_1_swipedown);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 114, 217);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_3_step_guide_phase_1);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj6 = obj;
            lv_obj_set_pos(obj, 245, 203);
            lv_obj_set_size(obj, 64, 29);
            lv_obj_add_event_cb(obj, event_handler_cb_onboarding1_obj6, LV_EVENT_ALL, flowState);
            lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj7 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Next");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj8 = obj;
            lv_obj_set_pos(obj, 134, 80);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_width(obj, 172, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_line_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Access WiFi, brightness, and Spotify connect with a downward swipe from anywhere on the screen.");
        }
    }
    
    tick_screen_onboarding1();
}

void tick_screen_onboarding1() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
}

void create_screen_onboarding2() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.onboarding2 = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj9 = obj;
            lv_obj_set_pos(obj, 11, 21);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_nunito_18_bold, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Widgets");
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 11, 71);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_onboarding_tutorial_2_leftright);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 114, 217);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_3_step_guide_phase_2);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj10 = obj;
            lv_obj_set_pos(obj, 245, 203);
            lv_obj_set_size(obj, 64, 29);
            lv_obj_add_event_cb(obj, event_handler_cb_onboarding2_obj10, LV_EVENT_ALL, flowState);
            lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj11 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Next");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj12 = obj;
            lv_obj_set_pos(obj, 134, 80);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_width(obj, 172, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_line_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Browse your widgets: weather, timers, and more by swiping left or right on the main screen.");
        }
    }
    
    tick_screen_onboarding2();
}

void tick_screen_onboarding2() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
}

void create_screen_onboarding3() {
    void *flowState = getFlowState(0, 4);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.onboarding3 = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj13 = obj;
            lv_obj_set_pos(obj, 11, 21);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_nunito_18_bold, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Always On Clock");
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 11, 71);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_onboarding_tutorial_3_swipeup);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 114, 217);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_3_step_guide_phase_3);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj14 = obj;
            lv_obj_set_pos(obj, 245, 203);
            lv_obj_set_size(obj, 64, 29);
            lv_obj_add_event_cb(obj, event_handler_cb_onboarding3_obj14, LV_EVENT_ALL, flowState);
            lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj15 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Finish");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj16 = obj;
            lv_obj_set_pos(obj, 134, 80);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_width(obj, 172, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_line_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Swipe up for a minimal always-on display that stays visible even when the screen is dimmed.");
        }
    }
    
    tick_screen_onboarding3();
}

void tick_screen_onboarding3() {
    void *flowState = getFlowState(0, 4);
    (void)flowState;
}

void create_screen_default_clock() {
    void *flowState = getFlowState(0, 5);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.default_clock = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // Volume Icon
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.volume_icon = obj;
            lv_obj_set_pos(obj, 21, 20);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_width(obj, 10193, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_height(obj, 10193, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // volumeLevel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.volume_level = obj;
            lv_obj_set_pos(obj, 38, 20);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // Wifi status
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_status = obj;
            lv_obj_set_pos(obj, 222, 19);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // Hour Default Clock
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.hour_default_clock = obj;
            lv_obj_set_pos(obj, 57, 95);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "hh");
        }
        {
            // Minute Default Clock
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.minute_default_clock = obj;
            lv_obj_set_pos(obj, 185, 95);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "hh");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 149, 95);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, ":");
        }
        {
            // dayDefaultClock
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.day_default_clock = obj;
            lv_obj_set_pos(obj, 147, 161);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "day");
        }
        {
            // dateDefaultClock
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.date_default_clock = obj;
            lv_obj_set_pos(obj, 144, 177);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "date");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj17 = obj;
            lv_obj_set_pos(obj, 82, 206);
            lv_obj_set_size(obj, 156, 24);
            lv_obj_add_event_cb(obj, event_handler_cb_default_clock_obj17, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // currentlyPlaying
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.currently_playing = obj;
            lv_obj_set_pos(obj, 92, 211);
            lv_obj_set_size(obj, 137, 15);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_AUTO);
            lv_obj_set_scroll_dir(obj, LV_DIR_LEFT);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_START);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "This love is so super duper hello");
        }
        {
            // Battery Icon
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.battery_icon = obj;
            lv_obj_set_pos(obj, 251, 19);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // Battery Percentage
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.battery_percentage = obj;
            lv_obj_set_pos(obj, 276, 19);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // wallpaperImage
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.wallpaper_image = obj;
            lv_obj_set_pos(obj, -1, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_default_clock();
}

void tick_screen_default_clock() {
    void *flowState = getFlowState(0, 5);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 0, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.volume_icon);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.volume_icon;
            lv_label_set_text(objects.volume_icon, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 2, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.volume_level);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.volume_level;
            lv_label_set_text(objects.volume_level, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 3, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.wifi_status);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.wifi_status;
            lv_label_set_text(objects.wifi_status, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 11, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.battery_icon);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.battery_icon;
            lv_label_set_text(objects.battery_icon, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 12, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.battery_percentage);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.battery_percentage;
            lv_label_set_text(objects.battery_percentage, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_quick_settings() {
    void *flowState = getFlowState(0, 6);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.quick_settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // Wifi Button
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.wifi_button = obj;
            lv_obj_set_pos(obj, 8, 68);
            lv_obj_set_size(obj, 70, 42);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][17]), LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][18]), LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][15]), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][16]), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][15]), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][16]), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][14]), LV_PART_MAIN | LV_STATE_CHECKED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "WiFi");
                }
            }
        }
        {
            // Bluetooth Button
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.bluetooth_button = obj;
            lv_obj_set_pos(obj, 86, 68);
            lv_obj_set_size(obj, 70, 42);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][17]), LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][18]), LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][15]), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][16]), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][15]), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][16]), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][14]), LV_PART_MAIN | LV_STATE_CHECKED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "BT");
                }
            }
        }
        {
            // Spotify Button
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.spotify_button = obj;
            lv_obj_set_pos(obj, 165, 68);
            lv_obj_set_size(obj, 70, 42);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][17]), LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][18]), LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][15]), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][16]), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][15]), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][16]), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][14]), LV_PART_MAIN | LV_STATE_CHECKED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Spotify");
                }
            }
        }
        {
            // DND Button
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.dnd_button = obj;
            lv_obj_set_pos(obj, 243, 68);
            lv_obj_set_size(obj, 70, 42);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][17]), LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][18]), LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][15]), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][16]), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][15]), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][16]), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][14]), LV_PART_MAIN | LV_STATE_CHECKED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "DND");
                }
            }
        }
        {
            // Brightness
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.brightness = obj;
            lv_obj_set_pos(obj, 33, 130);
            lv_obj_set_size(obj, 255, 22);
            lv_slider_set_range(obj, 10, 100);
            lv_slider_set_value(obj, 80, LV_ANIM_ON);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][12]), LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // Volume Slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.volume_slider = obj;
            lv_obj_set_pos(obj, 34, 168);
            lv_obj_set_size(obj, 255, 22);
            lv_slider_set_range(obj, 70, 80);
            lv_slider_set_value(obj, 75, LV_ANIM_ON);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][12]), LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // gesture_hint_quick_settings
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.gesture_hint_quick_settings = obj;
            lv_obj_set_pos(obj, 144, 227);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_t line_points[] = {
                { 0, 3 },
                { 32, 3 }
            };
            lv_line_set_points(obj, line_points, 2);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xa96363), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_height(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2b2b), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_line_rounded(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_line_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // OpenSettings
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.open_settings = obj;
            lv_obj_set_pos(obj, 8, 18);
            lv_obj_set_size(obj, 227, 31);
            lv_obj_add_event_cb(obj, event_handler_cb_quick_settings_open_settings, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj18 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Open Settings");
                }
            }
        }
        {
            // Power Button
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.power_button = obj;
            lv_obj_set_pos(obj, 252, 18);
            lv_obj_set_size(obj, 52, 31);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][19]), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj19 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj20 = obj;
            lv_obj_set_pos(obj, 13, 171);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj21 = obj;
            lv_obj_set_pos(obj, 296, 171);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // hidden home btn
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.hidden_home_btn = obj;
            lv_obj_set_pos(obj, 110, 215);
            lv_obj_set_size(obj, 100, 25);
            lv_obj_add_event_cb(obj, event_handler_cb_quick_settings_hidden_home_btn, LV_EVENT_ALL, flowState);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj22 = obj;
            lv_obj_set_pos(obj, 10, 133);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj23 = obj;
            lv_obj_set_pos(obj, 294, 133);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
    }
    
    tick_screen_quick_settings();
}

void tick_screen_quick_settings() {
    void *flowState = getFlowState(0, 6);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 15, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj19);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj19;
            lv_label_set_text(objects.obj19, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 16, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj20);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj20;
            lv_label_set_text(objects.obj20, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 17, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj21);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj21;
            lv_label_set_text(objects.obj21, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 19, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj22);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj22;
            lv_label_set_text(objects.obj22, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 20, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj23);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj23;
            lv_label_set_text(objects.obj23, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_media_pane() {
    void *flowState = getFlowState(0, 7);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.media_pane = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj29 = obj;
            lv_obj_set_pos(obj, 23, 11);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_width(obj, 1073741823, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_height(obj, 1073741823, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // spotifyVolumeIcon
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.spotify_volume_icon = obj;
            lv_obj_set_pos(obj, 23, 18);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_width(obj, 10193, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_height(obj, 10193, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // spotifyVolumeLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.spotify_volume_label = obj;
            lv_obj_set_pos(obj, 40, 18);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // Album Cover
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.album_cover = obj;
            lv_obj_set_pos(obj, 23, 47);
            lv_obj_set_size(obj, 118, 118);
            lv_img_set_src(obj, &img_default_album_cover);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_clip_corner(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // Play Pause
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.play_pause = obj;
            lv_obj_set_pos(obj, 137, 186);
            lv_obj_set_size(obj, 48, 48);
            lv_obj_add_event_cb(obj, event_handler_cb_media_pane_play_pause, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xcc2244), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_clip_corner(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj24 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][14]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // Previous Button
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.previous_button = obj;
            lv_obj_set_pos(obj, 23, 192);
            lv_obj_set_size(obj, 36, 36);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj30 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // Next Button
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.next_button = obj;
            lv_obj_set_pos(obj, 263, 192);
            lv_obj_set_size(obj, 36, 36);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj31 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // Song Title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.song_title = obj;
            lv_obj_set_pos(obj, 155, 60);
            lv_obj_set_size(obj, 137, 23);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Nothing Playing");
        }
        {
            // Artist Name
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.artist_name = obj;
            lv_obj_set_pos(obj, 156, 84);
            lv_obj_set_size(obj, 137, 23);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "No Artist");
        }
        {
            // Media Bar
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.media_bar = obj;
            lv_obj_set_pos(obj, 156, 117);
            lv_obj_set_size(obj, 143, 22);
            lv_slider_set_range(obj, 0, 100);
            lv_slider_set_mode(obj, LV_SLIDER_MODE_SYMMETRICAL);
            lv_slider_set_value(obj, 80, LV_ANIM_ON);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 32767, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_clip_corner(obj, true, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj25 = obj;
            lv_obj_set_pos(obj, 156, 141);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "0:00");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj26 = obj;
            lv_obj_set_pos(obj, 276, 142);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // shuffleButton
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.shuffle_button = obj;
            lv_obj_set_pos(obj, 232, 11);
            lv_obj_set_size(obj, 30, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_media_pane_shuffle_button, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_PRESSED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj27 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // loopButton
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.loop_button = obj;
            lv_obj_set_pos(obj, 269, 11);
            lv_obj_set_size(obj, 30, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_media_pane_loop_button, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj28 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "");
                }
            }
        }
        {
            // playingOn
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.playing_on = obj;
            lv_obj_set_pos(obj, 179, 160);
            lv_obj_set_size(obj, 120, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
            lv_obj_set_style_align(obj, LV_ALIGN_OUT_RIGHT_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
    }
    
    tick_screen_media_pane();
}

void tick_screen_media_pane() {
    void *flowState = getFlowState(0, 7);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 0, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj29);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj29;
            lv_label_set_text(objects.obj29, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 2, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.spotify_volume_icon);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.spotify_volume_icon;
            lv_label_set_text(objects.spotify_volume_icon, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 3, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.spotify_volume_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.spotify_volume_label;
            lv_label_set_text(objects.spotify_volume_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 6, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj24);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj24;
            lv_label_set_text(objects.obj24, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 8, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj30);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj30;
            lv_label_set_text(objects.obj30, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 10, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj31);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj31;
            lv_label_set_text(objects.obj31, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 13, 3, "Failed to evaluate Max in Slider widget");
        int32_t cur_val = lv_slider_get_max_value(objects.media_bar);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.media_bar;
            int16_t min = lv_slider_get_min_value(objects.media_bar);
            int16_t max = new_val;
            if (min < max) {
                lv_slider_set_range(objects.media_bar, min, max);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 15, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj26);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj26;
            lv_label_set_text(objects.obj26, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 17, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj27);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj27;
            lv_label_set_text(objects.obj27, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 20, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.playing_on);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.playing_on;
            lv_label_set_text(objects.playing_on, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_always_on_clock() {
    void *flowState = getFlowState(0, 8);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.always_on_clock = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // Always On Hour
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.always_on_hour = obj;
            lv_obj_set_pos(obj, 18, 16);
            lv_obj_set_size(obj, 142, 209);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_large_nunito_bold_114, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_decor(obj, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_line_space(obj, 0.01, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "09");
        }
        {
            // Always On Minute
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.always_on_minute = obj;
            lv_obj_set_pos(obj, 158, 134);
            lv_obj_set_size(obj, 187, 100);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_large_nunito_bold_114, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "14");
        }
        {
            // Always On Day
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.always_on_day = obj;
            lv_obj_set_pos(obj, 189, 74);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_38, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "day");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj32 = obj;
            lv_obj_set_pos(obj, 142, 55);
            lv_obj_set_size(obj, 37, 120);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_large_nunito_bold_114, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, ":");
        }
    }
    
    tick_screen_always_on_clock();
}

void tick_screen_always_on_clock() {
    void *flowState = getFlowState(0, 8);
    (void)flowState;
}

void create_screen_settings_page() {
    void *flowState = getFlowState(0, 9);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj33 = obj;
            lv_obj_set_pos(obj, 11, 63);
            lv_obj_set_size(obj, 302, 45);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj34 = obj;
                    lv_obj_set_pos(obj, 96, 1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // SettingsBackButton
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.settings_back_button = obj;
            lv_obj_set_pos(obj, 11, 8);
            lv_obj_set_size(obj, 32, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_page_settings_back_button, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj35 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][14]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj36 = obj;
            lv_obj_set_pos(obj, 528, -144);
            lv_obj_set_size(obj, 302, 45);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_page_obj36, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj37 = obj;
                    lv_obj_set_pos(obj, 96, 1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Connectivity");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj38 = obj;
                    lv_obj_set_pos(obj, 6, 7);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj39 = obj;
            lv_obj_set_pos(obj, 820, -22);
            lv_obj_set_size(obj, 302, 45);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_page_obj39, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj40 = obj;
                    lv_obj_set_pos(obj, 59, 1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Sounds and Vibration");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj41 = obj;
                    lv_obj_set_pos(obj, 6, 7);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj42 = obj;
            lv_obj_set_pos(obj, 847, 368);
            lv_obj_set_size(obj, 302, 45);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_page_obj42, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj43 = obj;
                    lv_obj_set_pos(obj, 59, 1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Display");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj44 = obj;
                    lv_obj_set_pos(obj, 6, 7);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj45 = obj;
            lv_obj_set_pos(obj, 960, 497);
            lv_obj_set_size(obj, 302, 45);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_page_obj45, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj46 = obj;
                    lv_obj_set_pos(obj, 59, 1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Battery");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj47 = obj;
                    lv_obj_set_pos(obj, 6, 7);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj48 = obj;
            lv_obj_set_pos(obj, 809, 593);
            lv_obj_set_size(obj, 302, 45);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_page_obj48, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj49 = obj;
                    lv_obj_set_pos(obj, 59, 1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Date & Time");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj50 = obj;
                    lv_obj_set_pos(obj, 6, 7);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj51 = obj;
            lv_obj_set_pos(obj, 1032, 705);
            lv_obj_set_size(obj, 302, 45);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_page_obj51, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj52 = obj;
                    lv_obj_set_pos(obj, 59, 1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Software Update");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj53 = obj;
                    lv_obj_set_pos(obj, 6, 7);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // settingsAboutDevice
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.settings_about_device = obj;
            lv_obj_set_pos(obj, 9, 120);
            lv_obj_set_size(obj, 302, 45);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_page_settings_about_device, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj54 = obj;
                    lv_obj_set_pos(obj, 59, 1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "About Device");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj55 = obj;
                    lv_obj_set_pos(obj, 6, 7);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj56 = obj;
            lv_obj_set_pos(obj, 125, 15);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_nunito_18_bold, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Settings");
        }
    }
    
    tick_screen_settings_page();
}

void tick_screen_settings_page() {
    void *flowState = getFlowState(0, 9);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 2, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj34);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj34;
            lv_label_set_text(objects.obj34, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 4, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj35);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj35;
            lv_label_set_text(objects.obj35, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 7, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj38);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj38;
            lv_label_set_text(objects.obj38, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 10, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj41);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj41;
            lv_label_set_text(objects.obj41, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 13, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj44);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj44;
            lv_label_set_text(objects.obj44, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 16, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj47);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj47;
            lv_label_set_text(objects.obj47, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 19, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj50);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj50;
            lv_label_set_text(objects.obj50, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 22, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj53);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj53;
            lv_label_set_text(objects.obj53, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 25, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj55);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj55;
            lv_label_set_text(objects.obj55, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_settings_connectivity() {
    void *flowState = getFlowState(0, 10);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings_connectivity = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    
    tick_screen_settings_connectivity();
}

void tick_screen_settings_connectivity() {
    void *flowState = getFlowState(0, 10);
    (void)flowState;
}

void create_screen_about_wavelet_1() {
    void *flowState = getFlowState(0, 11);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.about_wavelet_1 = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // wavelet_log_1
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.wavelet_log_1 = obj;
            lv_obj_set_pos(obj, 91, 31);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_wavelet_logo);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // SettingsBackButton_1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.settings_back_button_1 = obj;
            lv_obj_set_pos(obj, 10, 15);
            lv_obj_set_size(obj, 32, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_about_wavelet_1_settings_back_button_1, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj57 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][14]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 306, 88);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_3_step_guide_phase_1);
            lv_obj_set_style_transform_angle(obj, 900, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // Model Number
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.model_number = obj;
            lv_obj_set_pos(obj, 22, 106);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_nunito_18_bold, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Wavelet Mini 01");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj58 = obj;
            lv_obj_set_pos(obj, 22, 88);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Model");
        }
        {
            // Serial Number
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.serial_number = obj;
            lv_obj_set_pos(obj, 22, 153);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_nunito_18_bold, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "WVLT-MINI-XXXX");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj59 = obj;
            lv_obj_set_pos(obj, 22, 135);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Serial Number");
        }
        {
            // Uptime Duration
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.uptime_duration = obj;
            lv_obj_set_pos(obj, 22, 200);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_nunito_18_bold, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "8 months, 12 days, 4 hours");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj60 = obj;
            lv_obj_set_pos(obj, 22, 182);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Uptime");
        }
        {
            // SettingsBackButton_4
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.settings_back_button_4 = obj;
            lv_obj_set_pos(obj, 286, 153);
            lv_obj_set_size(obj, 32, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_about_wavelet_1_settings_back_button_4, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj61 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
    }
    
    tick_screen_about_wavelet_1();
}

void tick_screen_about_wavelet_1() {
    void *flowState = getFlowState(0, 11);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 3, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj57);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj57;
            lv_label_set_text(objects.obj57, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 12, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj61);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj61;
            lv_label_set_text(objects.obj61, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_about_wavelet_2() {
    void *flowState = getFlowState(0, 12);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.about_wavelet_2 = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // wavelet_log_2
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.wavelet_log_2 = obj;
            lv_obj_set_pos(obj, 91, 31);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_wavelet_logo);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // SettingsBackButton_2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.settings_back_button_2 = obj;
            lv_obj_set_pos(obj, 10, 15);
            lv_obj_set_size(obj, 32, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_about_wavelet_2_settings_back_button_2, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj62 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][14]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 306, 88);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_3_step_guide_phase_2);
            lv_obj_set_style_transform_angle(obj, 900, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // IP Address
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ip_address = obj;
            lv_obj_set_pos(obj, 22, 106);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_nunito_18_bold, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "192.168.X.X");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj63 = obj;
            lv_obj_set_pos(obj, 22, 88);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "IP Address");
        }
        {
            // Wifi Mac Address
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_mac_address = obj;
            lv_obj_set_pos(obj, 22, 153);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_nunito_18_bold, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "8C:7A:XX:XX:XX:XX");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj64 = obj;
            lv_obj_set_pos(obj, 22, 135);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "WiFi Mac address");
        }
        {
            // Bluetooth address
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.bluetooth_address = obj;
            lv_obj_set_pos(obj, 22, 200);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_nunito_18_bold, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "FE:80:XX:XX:XX:XX");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj65 = obj;
            lv_obj_set_pos(obj, 22, 182);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Bluetooth address");
        }
        {
            // SettingsBackButton_5
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.settings_back_button_5 = obj;
            lv_obj_set_pos(obj, 287, 153);
            lv_obj_set_size(obj, 32, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_about_wavelet_2_settings_back_button_5, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj66 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // SettingsBackButton_6
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.settings_back_button_6 = obj;
            lv_obj_set_pos(obj, 287, 55);
            lv_obj_set_size(obj, 32, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_about_wavelet_2_settings_back_button_6, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj67 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
    }
    
    tick_screen_about_wavelet_2();
}

void tick_screen_about_wavelet_2() {
    void *flowState = getFlowState(0, 12);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 3, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj62);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj62;
            lv_label_set_text(objects.obj62, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 12, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj66);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj66;
            lv_label_set_text(objects.obj66, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 14, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj67);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj67;
            lv_label_set_text(objects.obj67, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_about_wavelet_3() {
    void *flowState = getFlowState(0, 13);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.about_wavelet_3 = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // wavelet_log_3
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.wavelet_log_3 = obj;
            lv_obj_set_pos(obj, 91, 31);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_wavelet_logo);
            lv_obj_add_event_cb(obj, event_handler_cb_about_wavelet_3_wavelet_log_3, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // SettingsBackButton_3
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.settings_back_button_3 = obj;
            lv_obj_set_pos(obj, 10, 15);
            lv_obj_set_size(obj, 32, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_about_wavelet_3_settings_back_button_3, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj68 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][14]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 306, 88);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_3_step_guide_phase_3);
            lv_obj_set_style_transform_angle(obj, 900, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_qrcode_create(parent_obj, 125, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]));
            lv_obj_set_pos(obj, 22, 79);
            lv_obj_set_size(obj, 125, 125);
            lv_qrcode_update(obj, "https://github.com/serenebliss0/wavelet", 39);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            // SettingsBackButton_7
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.settings_back_button_7 = obj;
            lv_obj_set_pos(obj, 287, 55);
            lv_obj_set_size(obj, 32, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_about_wavelet_3_settings_back_button_7, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj69 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj70 = obj;
            lv_obj_set_pos(obj, 169, 85);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_nunito_18_bold, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Made with");
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 53, -8);
            lv_obj_set_size(obj, 17, 16);
            lv_img_set_src(obj, &img_heart);
            lv_img_set_zoom(obj, 25);
            lv_img_set_size_mode(obj, LV_IMG_SIZE_MODE_REAL);
            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj71 = obj;
            lv_obj_set_pos(obj, 194, 123);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_nunito_18_bold, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "from");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj72 = obj;
            lv_obj_set_pos(obj, 147, 151);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_nunito_18_bold, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Semire Designs");
        }
    }
    
    tick_screen_about_wavelet_3();
}

void tick_screen_about_wavelet_3() {
    void *flowState = getFlowState(0, 13);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 3, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj68);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj68;
            lv_label_set_text(objects.obj68, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 7, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj69);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj69;
            lv_label_set_text(objects.obj69, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_secret_page() {
    void *flowState = getFlowState(0, 14);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.secret_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(obj, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj73 = obj;
            lv_obj_set_pos(obj, 19, 26);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_inter_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Software Failure");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj74 = obj;
            lv_obj_set_pos(obj, 19, 53);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_inter_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Restart your device to continue");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj75 = obj;
            lv_obj_set_pos(obj, 19, 96);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_inter_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Guru Meditiation #00000004.0000AAC0");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj76 = obj;
            lv_obj_set_pos(obj, 19, 110);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_inter_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Illegal Instruction");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj77 = obj;
            lv_obj_set_pos(obj, 19, 153);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_inter_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "WVLT-MINI #WVLT.0001");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj78 = obj;
            lv_obj_set_pos(obj, 19, 26);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_large_nunito_bold_114, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, ": (");
        }
    }
    
    tick_screen_secret_page();
}

void tick_screen_secret_page() {
    void *flowState = getFlowState(0, 14);
    (void)flowState;
    {
        bool new_val = evalBooleanProperty(flowState, 6, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj78, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj78;
            if (new_val) {
                lv_obj_add_flag(objects.obj78, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.obj78, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_boot_splash,
    tick_screen_initial_qr_page,
    tick_screen_onboarding1,
    tick_screen_onboarding2,
    tick_screen_onboarding3,
    tick_screen_default_clock,
    tick_screen_quick_settings,
    tick_screen_media_pane,
    tick_screen_always_on_clock,
    tick_screen_settings_page,
    tick_screen_settings_connectivity,
    tick_screen_about_wavelet_1,
    tick_screen_about_wavelet_2,
    tick_screen_about_wavelet_3,
    tick_screen_secret_page,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 15) {
        tick_screen_funcs[screen_index]();
    }
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen(screenId - 1);
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
    { "Nunito-18", &ui_font_nunito_18 },
    { "Nunito-18 Bold", &ui_font_nunito_18_bold },
    { "Inter-10", &ui_font_inter_10 },
    { "Inter-7", &ui_font_inter_7 },
    { "font_icons", &ui_font_font_icons },
    { "Large Nunito Bold 114", &ui_font_large_nunito_bold_114 },
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
// Color themes
//

void change_color_theme(uint32_t theme_index) {
    {
        lv_obj_set_style_bg_color(objects.boot_splash, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        lv_obj_set_style_bg_color(objects.initial_qr_page, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_outline_color(objects.qr_token, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj0, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj1, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.obj4, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj4, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.generated_token_label, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        lv_obj_set_style_bg_color(objects.onboarding1, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj5, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.obj6, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj7, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj8, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        lv_obj_set_style_bg_color(objects.onboarding2, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj9, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.obj10, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj11, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj12, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        lv_obj_set_style_bg_color(objects.onboarding3, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj13, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.obj14, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj15, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj16, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        lv_obj_set_style_bg_color(objects.default_clock, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.volume_icon, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.wifi_status, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.hour_default_clock, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.minute_default_clock, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.day_default_clock, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.date_default_clock, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.obj17, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(objects.obj17, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.currently_playing, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.battery_icon, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.battery_percentage, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        lv_obj_set_style_bg_color(objects.quick_settings, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.wifi_button, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.wifi_button, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.wifi_button, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DISABLED);
        lv_obj_set_style_text_color(objects.wifi_button, lv_color_hex(theme_colors[theme_index][18]), LV_PART_MAIN | LV_STATE_DISABLED);
        lv_obj_set_style_bg_color(objects.wifi_button, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_text_color(objects.wifi_button, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_bg_color(objects.wifi_button, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
        lv_obj_set_style_text_color(objects.wifi_button, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
        lv_obj_set_style_bg_color(objects.wifi_button, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(objects.wifi_button, lv_color_hex(theme_colors[theme_index][14]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_bg_color(objects.bluetooth_button, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.bluetooth_button, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.bluetooth_button, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DISABLED);
        lv_obj_set_style_text_color(objects.bluetooth_button, lv_color_hex(theme_colors[theme_index][18]), LV_PART_MAIN | LV_STATE_DISABLED);
        lv_obj_set_style_bg_color(objects.bluetooth_button, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_text_color(objects.bluetooth_button, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_bg_color(objects.bluetooth_button, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
        lv_obj_set_style_text_color(objects.bluetooth_button, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
        lv_obj_set_style_bg_color(objects.bluetooth_button, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(objects.bluetooth_button, lv_color_hex(theme_colors[theme_index][14]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_bg_color(objects.spotify_button, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.spotify_button, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.spotify_button, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DISABLED);
        lv_obj_set_style_text_color(objects.spotify_button, lv_color_hex(theme_colors[theme_index][18]), LV_PART_MAIN | LV_STATE_DISABLED);
        lv_obj_set_style_bg_color(objects.spotify_button, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_text_color(objects.spotify_button, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_bg_color(objects.spotify_button, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
        lv_obj_set_style_text_color(objects.spotify_button, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
        lv_obj_set_style_bg_color(objects.spotify_button, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(objects.spotify_button, lv_color_hex(theme_colors[theme_index][14]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_bg_color(objects.dnd_button, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.dnd_button, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.dnd_button, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DISABLED);
        lv_obj_set_style_text_color(objects.dnd_button, lv_color_hex(theme_colors[theme_index][18]), LV_PART_MAIN | LV_STATE_DISABLED);
        lv_obj_set_style_bg_color(objects.dnd_button, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_text_color(objects.dnd_button, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_bg_color(objects.dnd_button, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
        lv_obj_set_style_text_color(objects.dnd_button, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
        lv_obj_set_style_bg_color(objects.dnd_button, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(objects.dnd_button, lv_color_hex(theme_colors[theme_index][14]), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_bg_color(objects.brightness, lv_color_hex(theme_colors[theme_index][13]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.brightness, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.brightness, lv_color_hex(theme_colors[theme_index][12]), LV_PART_KNOB | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.volume_slider, lv_color_hex(theme_colors[theme_index][13]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.volume_slider, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.volume_slider, lv_color_hex(theme_colors[theme_index][12]), LV_PART_KNOB | LV_STATE_DEFAULT);
        lv_obj_set_style_line_color(objects.gesture_hint_quick_settings, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.open_settings, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj18, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.power_button, lv_color_hex(theme_colors[theme_index][19]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj19, lv_color_hex(theme_colors[theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj20, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj21, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj22, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj23, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        lv_obj_set_style_bg_color(objects.media_pane, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.spotify_volume_icon, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.spotify_volume_label, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(objects.album_cover, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj24, lv_color_hex(theme_colors[theme_index][14]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.previous_button, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(objects.previous_button, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.next_button, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(objects.next_button, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.song_title, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.artist_name, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.media_bar, lv_color_hex(theme_colors[theme_index][13]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.media_bar, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.media_bar, lv_color_hex(theme_colors[theme_index][2]), LV_PART_KNOB | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj25, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj26, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.shuffle_button, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_text_color(objects.obj27, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj28, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.playing_on, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        lv_obj_set_style_bg_color(objects.always_on_clock, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.always_on_hour, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.always_on_minute, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.always_on_day, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj32, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        lv_obj_set_style_bg_color(objects.settings_page, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.obj33, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj34, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.settings_back_button, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(objects.settings_back_button, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj35, lv_color_hex(theme_colors[theme_index][14]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.obj36, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj37, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj38, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.obj39, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj40, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj41, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.obj42, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj43, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj44, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.obj45, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj46, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj47, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.obj48, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj49, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj50, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.obj51, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj52, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj53, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.settings_about_device, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj54, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj55, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj56, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        lv_obj_set_style_bg_color(objects.about_wavelet_1, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.settings_back_button_1, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(objects.settings_back_button_1, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj57, lv_color_hex(theme_colors[theme_index][14]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.model_number, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj58, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.serial_number, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj59, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.uptime_duration, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj60, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.settings_back_button_4, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(objects.settings_back_button_4, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj61, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        lv_obj_set_style_bg_color(objects.about_wavelet_2, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.settings_back_button_2, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(objects.settings_back_button_2, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj62, lv_color_hex(theme_colors[theme_index][14]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.ip_address, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj63, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.wifi_mac_address, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj64, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.bluetooth_address, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj65, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.settings_back_button_5, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(objects.settings_back_button_5, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj66, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.settings_back_button_6, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(objects.settings_back_button_6, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj67, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        lv_obj_set_style_bg_color(objects.about_wavelet_3, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.settings_back_button_3, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(objects.settings_back_button_3, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj68, lv_color_hex(theme_colors[theme_index][14]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.settings_back_button_7, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(objects.settings_back_button_7, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj69, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj70, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj71, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.obj72, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    lv_obj_invalidate(objects.boot_splash);
    lv_obj_invalidate(objects.initial_qr_page);
    lv_obj_invalidate(objects.onboarding1);
    lv_obj_invalidate(objects.onboarding2);
    lv_obj_invalidate(objects.onboarding3);
    lv_obj_invalidate(objects.default_clock);
    lv_obj_invalidate(objects.quick_settings);
    lv_obj_invalidate(objects.media_pane);
    lv_obj_invalidate(objects.always_on_clock);
    lv_obj_invalidate(objects.settings_page);
    lv_obj_invalidate(objects.settings_connectivity);
    lv_obj_invalidate(objects.about_wavelet_1);
    lv_obj_invalidate(objects.about_wavelet_2);
    lv_obj_invalidate(objects.about_wavelet_3);
    lv_obj_invalidate(objects.secret_page);
}
static const char *theme_names[] = { "Dark Mode", "Light Mode" };
uint32_t theme_colors[2][21] = {
    { 0xff0d0d0d, 0xff1a1a1a, 0xff222222, 0xff2a2a2a, 0xff333333, 0xfff0f0f0, 0xff888888, 0xff444444, 0xff1db954, 0xff4ade80, 0xffffb347, 0xffe63946, 0xffffffff, 0xffff4d6d, 0xfffaf1f9, 0xff211a2d, 0xffff4d6d, 0xff2d1f3a, 0xff6b5570, 0xffff8888, 0xff1a0a1a },
    { 0xfffaf1f9, 0xffffffff, 0xffffdef2, 0xfffdb6e1, 0xffe8c8e0, 0xff010a1a, 0xff6b3a6b, 0xffc4a8c4, 0xff1db954, 0xff16a34a, 0xffd97706, 0xffdc2626, 0xffffffff, 0xffff4d6d, 0xffffffff, 0xffffdef2, 0xffff4d6d, 0xfffdb6e1, 0xffc4a8c4, 0xffdc2626, 0xffffffff },
};

//
//
//

void create_screens() {
    
    eez_flow_init_fonts(fonts, sizeof(fonts) / sizeof(ext_font_desc_t));
    
    eez_flow_init_themes(theme_names, sizeof(theme_names) / sizeof(const char *), change_color_theme, &theme_colors[0][0], sizeof(theme_colors[0]) / sizeof(uint32_t));

// Set default LVGL theme
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    // Initialize screens
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));
    
    // Create screens
    create_screen_boot_splash();
    create_screen_initial_qr_page();
    create_screen_onboarding1();
    create_screen_onboarding2();
    create_screen_onboarding3();
    create_screen_default_clock();
    create_screen_quick_settings();
    create_screen_media_pane();
    create_screen_always_on_clock();
    create_screen_settings_page();
    create_screen_settings_connectivity();
    create_screen_about_wavelet_1();
    create_screen_about_wavelet_2();
    create_screen_about_wavelet_3();
    create_screen_secret_page();
}