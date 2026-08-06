#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_SETUP_DONE = 0,
    FLOW_GLOBAL_VARIABLE_COLOR_THEME = 1,
    FLOW_GLOBAL_VARIABLE_GENERATED_PAYLOAD_TOKEN = 2,
    FLOW_GLOBAL_VARIABLE_SUCCESSFUL_PAIR = 3,
    FLOW_GLOBAL_VARIABLE_IS_SPOTIFY_PLAYING = 4,
    FLOW_GLOBAL_VARIABLE_VOLUME_LEVEL = 5
};

// Native global variables

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/