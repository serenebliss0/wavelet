#pragma once
#include <FT6336.h>
#include "mini/MiniConfig.h"

extern unsigned short int width;
extern unsigned short int height;
extern unsigned short int min_x;
extern unsigned short int max_x;
extern unsigned short int min_y;
extern unsigned short int max_y;
extern unsigned short int rotation;

extern int touch_last_x;
extern int touch_last_y;

void touch_init(unsigned short int w, unsigned short int h,unsigned char r);
bool touch_touched(void);
bool touch_has_signal(void);
bool touch_released(void);




