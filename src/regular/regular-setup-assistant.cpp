//Wavelet Regular Setup Assistant

#include "regular-setup-assistant.h"

extern Preferences prefs; //global prefs instance
// 
AudioManager audio(prefs);
BluetoothA2DPSink a2dp_sink;

//uncomment this line to enable BatteryStats
#define BATTERIES_CONNECTED

void initializeGPIO(){
    pinMode(Config::BUZZER, OUTPUT);
    pinMode(Config::PWR_BUTTON, INPUT_PULLUP);
    pinMode(Config::PREVIOUS_BUTTON, INPUT_PULLUP);
    pinMode(Config::NEXT_BUTTON, INPUT_PULLUP);
    pinMode(Config::PAUSE_BUTTON, INPUT_PULLUP);
}

void initializeI2S(){
    i2s_pin_config_t my_pins = {
        .bck_io_num = 26,
        .ws_io_num = 25,
        .data_out_num = 4, //DIN
        .data_in_num = I2S_PIN_NO_CHANGE
    };
    
    a2dp_sink.set_pin_config(my_pins);
    a2dp_sink.set_on_connection_state_changed(on_connected);
    a2dp_sink.set_auto_reconnect(false);
}

void startA2DP(){
    a2dp_sink.start("Wavelet");
}

void playDebugBeep(){
    audio.buzz(1000,1000);

}

void playStartupSound(){
    audio.play_startup_sound();

}

void handleButtons(){
    // handlePowerButton();
    handlePreviousButton();
    handleNextButton();
}

bool setupDone = false;

void initializePreferences() {
    extern Preferences prefs;

    setupDone = prefs.getBool("setup_done", false);

    Serial.printf(
        "[NVS] setup_done = %s\n",
        setupDone ? "true" : "false"
    );
}

void startOrCheckOnboarding(){


    if(!setupDone){

        beginSetupMode("regular", "pink"); //BLEManager entry point

    }
    else{
        // BLE remains available for companion-app controls after setup.
        initBLE("regular", "pink");
        initializeGPIO();
        // initializeI2S();
        // startA2DP();
        // handleButtons();
        playStartupSound();
    }
}
