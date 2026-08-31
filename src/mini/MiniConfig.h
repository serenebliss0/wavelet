#pragma once

//Configuration file for the Wavelet Mini
//If you are looking for the regular's config:
// src/Config.h


//Contains pins, and other params
namespace MiniConfig {

    //Audio 
    constexpr int LED_PIN = 42;
    constexpr int BATTERY_PIN = 9;
    constexpr int BUZZER = 27;


    //Pwr and Mode
    constexpr int PWR_BUTTON = 23;
    constexpr int MODE_BUTTON = 21;
    
    constexpr const char* deviceName = "Wavelet";

}

//Display
//Pins
constexpr int TOUCH_FT6336_SCL = 15;
constexpr int TOUCH_FT6336_SDA = 16;
constexpr int TOUCH_FT6336_INT = 17;
constexpr int TOUCH_FT6336_RST = 18;
//Other param
constexpr int TOUCH_MAP_X1 = 0;
constexpr int TOUCH_MAP_X2 = 240;
constexpr int TOUCH_MAP_Y1 = 0;
constexpr int TOUCH_MAP_Y2 = 320;

//Battery
constexpr float ADC_REFERENCE = 3.3f;
constexpr int ADC_RESOLUTION = 4095;
constexpr float VOLTAGE_DIVIDER = 2.0f;

//SD Card
constexpr int SD_CLK = 38;
constexpr int SD_CMD = 40;
constexpr int SD_D0 = 39;
constexpr int SD_D1  = 41;
constexpr int SD_D2  = 48;
constexpr int SD_D3  = 47;

//Buttons
const int PLAY_BUTTON = 2; //play/pause
const int VOL_UP_BUTTON = 3;
const int VOL_DOWN_BUTTON  = 14;

//Audio
const int AUDIO_I2C_SDA = 16;   //(shared with touch + extended I2C)
const int AUDIO_I2C_SCL = 15;   //(shared with touch + extended I2C)
const int AUDIO_I2S_MCLK = 4;
const int AUDIO_I2S_BCK = 5;
const int AUDIO_I2S_DOUT = 8;
const int AUDIO_I2S_WS  = 7;
const int AUDIO_AMP_ENABLE  = 1;