#include "Spotify.h"
#include <Secrets.h>
#include "album_art.h"
#include "mini/MiniConfig.h"
#include "mini/storage/logger.h"


Spotify sp(CLIENT_ID, CLIENT_SECRET, REFRESH_TOKEN);

struct ButtonState {
    int pin;
    bool lastReading = HIGH;
    bool debounced   = HIGH;
    unsigned long lastChangeMs = 0;

    ButtonState(int p) : pin(p) {}   // constructor
};

static const unsigned long DEBOUNCE_MS = 30;

static ButtonState playBtn { PLAY_BUTTON };

static bool buttonsReady = false;

static bool pollButtonPressed(ButtonState &btn) {
    bool reading = digitalRead(btn.pin);

    if (reading != btn.lastReading) {
        btn.lastChangeMs = millis();
        btn.lastReading = reading;
    }

    if ((millis() - btn.lastChangeMs) > DEBOUNCE_MS && reading != btn.debounced) {
        btn.debounced = reading;
        if (btn.debounced == LOW) return true;
    }

    return false;
}

static void initializeButtons() {
    if (PLAY_BUTTON < 0 ) {
        Serial.println("[SPOTIFY] Button pins not set — skipping button init");
        Logger::warning("Spotify", "Button pins not set — skipping button init");
        return;
    }

    pinMode(PLAY_BUTTON, INPUT_PULLUP);
    buttonsReady = true;
}


String lastTrack  = "";
String lastArtist = "";
bool lastPlaying  = false;

unsigned long lastUpdate = 0;
const unsigned long SPOTIFY_UPDATE_INTERVAL = 5000;

//initialization and authorization
void initializeSpotify() {

    Serial.printf("[DEBUG] Free heap: %d, Largest free block: %d\n",
        ESP.getFreeHeap(), heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));

    Serial.println("[SPOTIFY] Initializing...");
    initializeButtons();
    Serial.println("[SPOTIFY] Init complete");
    Logger::info("Spotify", "Spotify was initialized successfully");
}

bool authenticateSpotify() {
    Serial.println("[SPOTIFY] Starting authentication...");
    sp.set_log_level(SPOTIFY_LOG_VERBOSE);

    sp.begin();
    while (!sp.is_auth()) {
        sp.handle_client();
    }

    Serial.printf("[SPOTIFY] Authenticated! Refresh token: %s\n",
                sp.get_user_tokens().refresh_token);

    return true;
}


void getCurrentlyPlaying() {
    JsonDocument filter;
    filter["is_playing"] = true;
    filter["item"]["name"] = true;
    filter["item"]["artists"][0]["name"] = true;
    filter["item"]["album"]["id"] = true;
    filter["item"]["album"]["images"] = true;

    response res = sp.get_currently_playing_track(filter);

    if (res.status_code == -1) {
        Serial.println("[SPOTIFY] Connection dead, forcing reconnect...");
        WiFi.disconnect();
        delay(100);
        WiFi.reconnect();
        return; // skip parsing, try again next cycle
    }

    if (res.status_code != 200) return;
    
    bool playing = res.reply["is_playing"];
    String track = res.reply["item"]["name"].as<String>();
    String albumId = res.reply["item"]["album"]["id"].as<String>();
    
    String artist = "";
    for (JsonObject a : res.reply["item"]["artists"].as<JsonArray>()) {
        if (artist.length() > 0) artist += ", ";
        artist += a["name"].as<String>();
    }
    
    checkAndCacheAlbumArt(albumId, res.reply); // new line
    
    if (playing != lastPlaying || track != lastTrack || artist != lastArtist) {
        lastTrack = track;
        lastArtist = artist;
        lastPlaying = playing;
    }
}

void pauseCurrentlyPlaying() {
    if (sp.is_playing()) {
        response res = sp.pause_playback();
        Serial.print("[SPOTIFY] Pause: "); Serial.println(res.status_code);
    } else {
        response res = sp.start_a_users_playback();
        Serial.print("[SPOTIFY] Resume: "); Serial.println(res.status_code);
    }
}

void playNextSong() {
    response res = sp.skip_to_next();
    Serial.print("[SPOTIFY] Next: "); Serial.println(res.status_code);
}

void playPreviousSong() {
    response res = sp.skip_to_previous();
    Serial.print("[SPOTIFY] Previous: "); Serial.println(res.status_code);
}

//Helper functions
void playCurrentTrack() {
    response res = sp.start_a_users_playback();
    Serial.print("[SPOTIFY] Play: "); Serial.println(res.status_code);
}

void seekTo(int position_ms) {
    response res = sp.seek_to_position(position_ms);
    Serial.print("[SPOTIFY] Seek: "); Serial.println(res.status_code);
}

void setPlaybackVolume(int volume_percent) {
    response res = sp.set_volume(volume_percent);
    Serial.print("[SPOTIFY] Volume: "); Serial.println(res.status_code);
}

void enableShuffle() {
    response res = sp.toggle_shuffle(spotify_types::SHUFFLE_ON);
    Serial.print("[SPOTIFY] Shuffle ON: "); Serial.println(res.status_code);
}

void disableShuffle() {
    response res = sp.toggle_shuffle(spotify_types::SHUFFLE_OFF);
    Serial.print("[SPOTIFY] Shuffle OFF: "); Serial.println(res.status_code);
}

// Spotify's repeat modes: off / track / context (playlist or album)
void setRepeatOff() {
    response res = sp.set_repeat_mode(spotify_types::REPEAT_OFF);
    Serial.print("[SPOTIFY] Repeat OFF: "); Serial.println(res.status_code);
}

void setRepeatTrack() {
    response res = sp.set_repeat_mode(spotify_types::REPEAT_TRACK);
    Serial.print("[SPOTIFY] Repeat TRACK: "); Serial.println(res.status_code);
}

void setRepeatContext() {
    response res = sp.set_repeat_mode(spotify_types::REPEAT_CONTEXT);
    Serial.print("[SPOTIFY] Repeat CONTEXT: "); Serial.println(res.status_code);
}

//Button handler
static void handleButtons() {
    if (!buttonsReady) return;

    if (pollButtonPressed(playBtn))  pauseCurrentlyPlaying();
}

//call this in main loop
void updateSpotify() {
    handleButtons();

    if (millis() - lastUpdate >= SPOTIFY_UPDATE_INTERVAL) {
        lastUpdate = millis();
        getCurrentlyPlaying();
    }
}