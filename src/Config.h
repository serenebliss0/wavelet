#pragma once

//Configuration file for Wavelet Regular

//If you are looking for the mini's config:
// src/mini/MiniConfig.h

namespace Config {

    //Audio 
    constexpr int VOLUME_POT = 34;
    constexpr int VOL_THRESHOLD = 10;
    constexpr int BUZZER = 27;

    constexpr int PREVIOUS_BUTTON = 19;
    constexpr int NEXT_BUTTON = 18;
    constexpr int PAUSE_BUTTON = 13;

    //Pwr and Mode
    constexpr int PWR_BUTTON = 23;
    constexpr int MODE_BUTTON = 21;
    
    constexpr const char* deviceName = "Wavelet";

}