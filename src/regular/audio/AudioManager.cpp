#include "AudioManager.h"
#include "BluetoothA2DPSink.h"
#include "driver/i2s.h"
#include "Config.h"
#include "Sounds.h" //Contains all sounds
#define DEBUG

extern BluetoothA2DPSink a2dp_sink;

int volumeLevel = 0;
int rememberedVolume = 0;

AudioManager::AudioManager(Preferences& prefsRef)
    : prefs(prefsRef) {}


void AudioManager::buzz(int freq, int duration) {
    tone(Config::BUZZER, freq, duration); // play tone
    delay(duration);                  // wait
    noTone(Config::BUZZER);               // stop
}




void AudioManager::play_connected_sound() {
  // reconfigure I2S for the WAV's specs
  i2s_set_clk(I2S_NUM_0, 11025, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);

  const uint8_t* pcm_data = connected_sound + 44;
  size_t pcm_len = sizeof(connected_sound) - 44;

  size_t bytes_written = 0;
  i2s_write(I2S_NUM_0, pcm_data, pcm_len, &bytes_written, portMAX_DELAY);

  // restore I2S for A2DP (44100 stereo)
  i2s_set_clk(I2S_NUM_0, 44100, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_STEREO);

  #ifdef DEBUG
  Serial.println("Conencted sound was played");
  #endif
}

void AudioManager::play_shutdown_sound() {
  i2s_set_clk(I2S_NUM_0, 11025, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);

  const uint8_t* pcm_data = shutdown_sound + 44;
  size_t pcm_len = sizeof(shutdown_sound) - 44;

  size_t bytes_written = 0;
  i2s_write(I2S_NUM_0, pcm_data, pcm_len, &bytes_written, portMAX_DELAY);

  i2s_set_clk(I2S_NUM_0, 44100, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_STEREO);

  #ifdef DEBUG
  Serial.println("Shutdown sound was played");
  #endif
}

void AudioManager::play_startup_sound() {
  i2s_set_clk(I2S_NUM_0, 11025, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);

  const uint8_t* pcm_data = startup_sound + 44;
  size_t pcm_len = sizeof(startup_sound) - 44;

  size_t bytes_written = 0;
  i2s_write(I2S_NUM_0, pcm_data, pcm_len, &bytes_written, portMAX_DELAY);

  i2s_set_clk(I2S_NUM_0, 44100, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_STEREO);

  #ifdef DEBUG
  Serial.println("Startup sound was played");
  #endif
}

void AudioManager::updateVolume()
{
    volumeLevel = analogRead(Config::VOLUME_POT);
    int volume = map(volumeLevel, 0, 4095, 0, 127); // map to 0–127
    if (abs(volume - LAST_VOLUME) >= Config::VOL_THRESHOLD) {
    a2dp_sink.set_volume(volume);
    LAST_VOLUME = volume;

    prefs.begin("volume", false);
    rememberedVolume = prefs.putInt("volume", volume);
    prefs.end();
}
  delay(50);

  #ifdef DEBUG
    //Serial.print("Potentiometer value at: ");
    //Serial.println(volumeLevel);
  #endif
}
