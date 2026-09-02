//Wavelet Mini Setup Assistant

#include "mini/mini-setup-assistant.h"

//Setting up display for MINI
// TODO: Give each model its own module and free up main.cpp

//display config
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 240;
static lv_disp_draw_buf_t disp_buf;
static lv_color_t buf[screenWidth * 30];


TFT_eSPI my_lcd = TFT_eSPI();

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    my_lcd.setAddrWindow(area->x1, area->y1, w, h);
    my_lcd.pushColors((uint16_t *)&color_p->full, w * h, true);
    lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
    if (touch_touched()) {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = touch_last_x;
        data->point.y = touch_last_y;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}


//TODO: move to display init module

void initializeDisplay() {
my_lcd.init();
my_lcd.fillScreen(0x0000); //Black by default
my_lcd.setRotation(1);

touch_init(my_lcd.width(), my_lcd.height(), my_lcd.getRotation());

lv_init();
delay(10);

lv_disp_draw_buf_init(&disp_buf, buf, NULL, screenWidth * 30);

static lv_disp_drv_t disp_drv;
lv_disp_drv_init(&disp_drv);
disp_drv.hor_res = my_lcd.width();
disp_drv.ver_res = my_lcd.height();
disp_drv.flush_cb = my_disp_flush;
disp_drv.draw_buf = &disp_buf;
lv_disp_drv_register(&disp_drv);

static lv_indev_drv_t indev_drv;
lv_indev_drv_init(&indev_drv);
indev_drv.type = LV_INDEV_TYPE_POINTER;
indev_drv.read_cb = my_touchpad_read;
lv_indev_drv_register(&indev_drv);
}

//Start LED
void startLED(){
    ledInit();
    ledSetState(LedState::BOOT);
}

//Change led state to boot

bool setupDone;
//NVS for mini
void initializePreferences(){
Preferences prefs;
prefs.begin("wavelet", true);
bool setupDone = prefs.getBool("setup_done", false);
prefs.end();
}

String payload = "";
String token = getOrCreateSetupToken();

void initializeLVGL(){
    //init LVGL UI and create screens
    ui_init();
    create_screens();    //init LVGL UI and create screens
}

// //debug only, negate logic in prod
void startOrCheckOnboarding(){

if (!setupDone) {
    //Change later
    //Color picker later
    beginSetupMode("mini", "strawberry_pink");
    payload = getSetupPayload();
    #ifdef DEBUG
    printQRToSerial(payload);
    #endif

    initializeLVGL();

    //change the qrcode to the generated payload
    lv_qrcode_update(
        objects.obj0,
        payload.c_str(),
        payload.length()
    );
    //change the manual code to the token
    lv_label_set_text(
        objects.obj6,
        token.c_str()
    );
}

//when other screens are ready
//add second condition
}

//Init filesystem
void initializeSD(){SDManager::begin();}


void initializeWiFi(){
    if (hasStoredWifiCredentials()) {
        beginWifiManager();
        while (!isWifiManagerDone()) {
            processWifiManager();
            delay(10);
        }
    }
}

void startSpotify(){
    if (WiFi.status() == WL_CONNECTED) {
    //Gate features requiring wifi
        initializeSpotify();
        authenticateSpotify();
    }
}

void startFeatures(){
    initializeSD();
    initializeWiFi();
    startSpotify();
}



