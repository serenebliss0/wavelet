#pragma once  // stops the file being included twice
#include <Arduino.h>
#include <Preferences.h>

extern int volumeLevel;
extern int rememberedVolume;

class AudioManager {
public:
AudioManager(Preferences& prefsRef);
void begin();           // declare functions here
void play_connected_sound();
void play_shutdown_sound();
void play_startup_sound();
void buzz(int freq, int duration);
void setVolume(int v);
void updateVolume();
void initAudio();

private:
Preferences& prefs;
int LAST_VOLUME = -1;

};
