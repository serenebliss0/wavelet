#include "battery.h"

#include "mini/storage/logger.h"
#include "mini/MiniConfig.h"

constexpr uint8_t BATTERY_PIN = MiniConfig::BATTERY_PIN;          // Replace with the correct analog pin
// constexpr uint8_t CHARGE_PIN = MiniConfig::BATTERY_PIN;           // TODO
constexpr float ADC_REFERENCE = 3.3f;
constexpr int ADC_RESOLUTION = 4095;
constexpr float VOLTAGE_DIVIDER = 2.0f;

struct BatteryData
{
    float voltage = 0.0f;
    uint8_t percentage = 0;

    bool charging = false;
    bool full = false;
};

static BatteryData battery;

bool Battery::begin()
{
    analogReadResolution(12);

    analogSetPinAttenuation(
        BATTERY_PIN,
        ADC_11db);

    // pinMode(CHARGE_PIN, INPUT);

    Logger::info(
        "Battery",
        "Initialized.");

    return true;
}

static float readVoltage()
{
    long total = 0;

    for(int i = 0; i < 10; i++)
    {
        total += analogRead(BATTERY_PIN);
    }

    float raw = total / 10.0f;

    float adcVoltage =
        (raw / ADC_RESOLUTION) * ADC_REFERENCE;

    return adcVoltage * VOLTAGE_DIVIDER;
}


static uint8_t voltageToPercent(float voltage)
{
    if(voltage <= 2.5f)
        return 0;

    if(voltage >= 4.2f)
        return 100;

    return (uint8_t)((voltage - 2.5f) * 100.0f / 1.7f);
}

void Battery::update()
{
    static uint32_t previous = 0;

    if(millis() - previous < 1000)
        return;

    previous = millis();

    battery.voltage = readVoltage();

    battery.percentage =
        voltageToPercent(battery.voltage);

    battery.charging =
        // digitalRead(CHARGE_PIN);

    battery.full =
        battery.charging &&
        battery.percentage >= 99;
}


float Battery::voltage()
{
    return battery.voltage;
}

uint8_t Battery::percentage()
{
    return battery.percentage;
}

bool Battery::charging()
{
    return battery.charging;
}

bool Battery::full()
{
    return battery.full;
}

bool Battery::low()
{
    return battery.percentage <= 15;
}

bool Battery::critical()
{
    return battery.percentage <= 5;
}