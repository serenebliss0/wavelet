#include "Buttons.h"

#include <Arduino.h>
#include "BluetoothA2DPSink.h"

#include "regular/audio/AudioManager.h"
#include "regular/core/Speaker.h"
#include "Config.h"

#define DEBUG

extern BluetoothA2DPSink a2dp_sink;
extern AudioManager audio;

unsigned long pwrPressStart = 0;
bool pwrHeld = false;

void handlePowerButton() {
  if (digitalRead(Config::PWR_BUTTON) == LOW) 
  { 
    if (pwrPressStart == 0) 
    {
      pwrPressStart = millis(); // start timing
    }

    if (millis() - pwrPressStart > 2000 && !pwrHeld) 
    { // 2 sec hold
      pwrHeld = true;
      // long press action here

      #ifdef DEBUG
      Serial.println("Long press - shutting down!");
      #endif

      audio.play_shutdown_sound();
      a2dp_sink.end(); // gracefully disconnect Bluetooth
      delay(500);
      esp_sleep_enable_ext0_wakeup(GPIO_NUM_23, 0); // wake when PWR_BUTTON goes LOW
      esp_deep_sleep_start();
    }
  } 
  else 
  {
    // button released
    if (pwrPressStart != 0 && !pwrHeld) 
    {
      // short press action here
      Serial.println("Short press - sleep/wake!");
    }

    pwrPressStart = 0;
    pwrHeld = false;
  }
}

void handlePreviousButton() {
  static bool wasPressed = false;
  bool isPressed = digitalRead(Config::PREVIOUS_BUTTON) == LOW;
  
  if (isPressed && !wasPressed) {
    a2dp_sink.previous();
  }
  wasPressed = isPressed;
}

void handleNextButton() {
  static bool wasPressed = false;
  bool isPressed = digitalRead(Config::NEXT_BUTTON) == LOW;
  
  if (isPressed && !wasPressed) {
    a2dp_sink.next();
  }
  wasPressed = isPressed;
}
