#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#include "mini/MiniConfig.h"
#include "NeoPixel.h"

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  60

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 50 // Set BRIGHTNESS to about 1/5 (max = 255)

static LedState currentState = LedState::OFF; //set the default state to off

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, MiniConfig::LED_PIN, NEO_GRBW + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
}

void loop() {
    ledUpdate();
}

void ledInit()
{
    strip.begin();
    strip.clear();
    strip.show();
}

void ledSetState(LedState state)
{
    currentState = state;
}

LedState ledGetState()
{
    return currentState;
}


void chargingAnimation()
{
    static uint32_t lastUpdate = 0;
    static int brightness = 0;
    static int direction = 5;

    if (millis() - lastUpdate < 20)
        return;

    lastUpdate = millis();

    brightness += direction;

    if (brightness >= 255)
        direction = -5;

    if (brightness <= 0)
        direction = 5;

    strip.setBrightness(brightness);
    strip.setPixelColor(0, strip.Color(74, 222, 128));
    strip.show();
}

void lowBatteryAnimation()
{
    static uint32_t lastUpdate = 0;
    static int brightness = 0;
    static int direction = 5;

    if (millis() - lastUpdate < 5)
        return;

    lastUpdate = millis();

    brightness += direction;

    if (brightness >= 255)
        direction = -5;

    if (brightness <= 0)
        direction = 5;

    strip.setBrightness(brightness);
    strip.setPixelColor(0, strip.Color(255, 0, 0));
    strip.show();
}

void errorState() {
    strip.setPixelColor(0, strip.Color(255,0,0));
    strip.setPixelColor(0, strip.Color(0, 255, 0));
    strip.setPixelColor(0, strip.Color(0,0,255));
}

void ledUpdate()
{
    switch(currentState)
    {
        case LedState::OFF:
            strip.clear();
            break;

        case LedState::READY:
            strip.clear();
            break;

        case LedState::PAIRING:
            strip.setPixelColor(0, strip.Color(0,0,255));
            break;

        case LedState::CHARGING:
            chargingAnimation();
            break;

        case LedState::CHARGED:
            strip.setPixelColor(0, strip.Color(0,255,0));
            break;

        case LedState::LOW_BATTERY:
            lowBatteryAnimation();
            break;

        case LedState::ERROR:
            errorState();
            break;

        case LedState::BOOT:
            strip.setPixelColor(0, strip.Color(255,255,255));
            break;
    }

    strip.show();
}