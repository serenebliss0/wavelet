/*
 * This project uses LVGL 8.4. Keep the full LVGL 8 configuration here so the
 * generated EEZ screens retain their enabled fonts and QR code support.
 */
#pragma once
#include <src/lv_conf.h>
#undef LV_MEM_POOL_INCLUDE
#undef LV_MEM_POOL_ALLOC
#define LV_MEM_POOL_INCLUDE "wavelet_lvgl_psram.h"
#define LV_MEM_POOL_ALLOC wavelet_lvgl_psram_pool
