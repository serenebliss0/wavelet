#pragma once

#include <stddef.h>
#include "esp_heap_caps.h"

// LVGL/EEZ objects are CPU-accessed; keep their pool in PSRAM so TLS and
// hardware crypto retain contiguous internal/DMA-capable memory.
static inline void* wavelet_lvgl_psram_pool(size_t size) {
    return heap_caps_malloc(size, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
}
