#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_wavelet_logo;
extern const lv_img_dsc_t img_mini_manual_code_box_initialpair;
extern const lv_img_dsc_t img_onboarding_tutorial_1_swipedown;
extern const lv_img_dsc_t img_3_step_guide_phase_1;
extern const lv_img_dsc_t img_onboarding_tutorial_2_leftright;
extern const lv_img_dsc_t img_3_step_guide_phase_2;
extern const lv_img_dsc_t img_3_step_guide_phase_3;
extern const lv_img_dsc_t img_onboarding_tutorial_3_swipeup;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[8];

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/