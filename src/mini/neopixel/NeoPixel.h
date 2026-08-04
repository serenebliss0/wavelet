#pragma once

enum class LedState {
    OFF,
    BOOT,
    READY,
    PAIRING,
    CHARGING,
    CHARGED,
    LOW_BATTERY,
    ERROR
};

void ledInit();
void ledSetState(LedState state);
LedState ledGetState();
void ledUpdate();