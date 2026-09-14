#include "Speaker.h"
#include <Arduino.h>

#include "regular/audio/AudioManager.h"

#define DEBUG

extern BluetoothA2DPSink a2dp_sink;
extern AudioManager audio;

void on_connected(esp_a2d_connection_state_t state, void* ptr) {
  if (state == ESP_A2D_CONNECTION_STATE_CONNECTED) {
    audio.play_connected_sound();
    audio.buzz(1000,1000);
  }
}
