#pragma once

#include <Arduino.h>

void miniVolumeInitialize();
uint8_t miniVolumeGetPercent();
int miniVolumeCodecLevel();
void miniVolumeSetPercent(uint8_t percent, bool persist = true);
void miniVolumeBindUi();
