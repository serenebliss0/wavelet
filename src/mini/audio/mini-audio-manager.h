#pragma once

#include <Arduino.h>

// AudioManager
//
// Handles the ES8311 codec + I2S output on Wavelet Mini.
// Scope: short local WAV playback only (boot chime, notifications, alarms).
// No streaming decode, no mic input.
//
// I2C NOTE: the ES8311's SDA/SCL pins are shared with the FT6336 touch
// controller (confirmed on the board's datasheet). Both this driver and
// FT6336 talk over the same Wire instance for that reason -- whichever
// manager runs first should call Wire.begin(), and the other should not
// call it again. On Mini that's expected to be the touch manager, since
// touch/UI typically comes up before audio. Pass initializeI2CBus=true
// to begin() ONLY if AudioManager is guaranteed to run before touch.

class AudioManager
{
public:
    static bool begin(bool initializeI2CBus = false);

    // Queues a WAV file for playback. Non-blocking -- decode/streaming
    // happens on the audio task. Only one file plays at a time; calling
    // this while something is already playing stops the current sound
    // and starts the new one.
    static bool play(const char* path);

    static void stop();

    static void setVolume(int volume); // 0-100
    static void mute(bool enable);
    static bool isPlaying();

private:
    static void audioTask(void* param);
    static bool playFileInternal(const char* path);
    static bool configureCodecForRate(uint32_t sampleRate);
};