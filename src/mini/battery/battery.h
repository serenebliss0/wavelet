#pragma once

#include <Arduino.h>

namespace Battery
{
    bool begin();
    void update();

    float voltage();
    uint8_t percentage();

    bool charging();
    bool full();

    bool low();
    bool critical();
}