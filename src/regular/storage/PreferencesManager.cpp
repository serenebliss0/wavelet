#include "PreferencesManager.h"

#include <Preferences.h>

extern Preferences prefs;

int readRememberedVolume() {
  //read saved preferences
  prefs.begin("wavelet", true); // read-only
  int rememberedVolume = prefs.getInt("volume", 50);
  // prefs.end();

  return rememberedVolume;
}
