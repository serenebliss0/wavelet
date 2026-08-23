#include "Spotify.h"
#include <Secrets.h>
#include "album_art.h"


Spotify sp(CLIENT_ID, CLIENT_SECRET, REFRESH_TOKEN);

// ─────────────────────────────────────────────────────────────────────────────
// Buttons
// ⚠️ PLACEHOLDER PINS — set these to confirmed free GPIOs before use.
// initializeButtons() will refuse to run while any of these are -1, so
// leaving them unset just skips button support instead of corrupting memory.
// ─────────────────────────────────────────────────────────────────────────────

const int PLAY_BUTTON = 2;
const int PREV_BUTTON = 3;
const int NXT_BUTTON  = 14;

struct ButtonState {
    int pin;
    bool lastReading = HIGH;
    bool debounced   = HIGH;
    unsigned long lastChangeMs = 0;

    ButtonState(int p) : pin(p) {}   // <-- this line was missing
};

static const unsigned long DEBOUNCE_MS = 30;

static ButtonState playBtn { PLAY_BUTTON };
static ButtonState prevBtn { PREV_BUTTON };
static ButtonState nextBtn { NXT_BUTTON };

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
    if (PLAY_BUTTON < 0 || PREV_BUTTON < 0 || NXT_BUTTON < 0) {
        Serial.println("[SPOTIFY] Button pins not set — skipping button init");
        return;
    }

    pinMode(PLAY_BUTTON, INPUT_PULLUP);
    pinMode(PREV_BUTTON, INPUT_PULLUP);
    pinMode(NXT_BUTTON,  INPUT_PULLUP);
    buttonsReady = true;
}

// ─────────────────────────────────────────────────────────────────────────────
// Playback state / timing
// ─────────────────────────────────────────────────────────────────────────────

String lastTrack  = "";
String lastArtist = "";
bool lastPlaying  = false;

unsigned long lastUpdate = 0;
const unsigned long SPOTIFY_UPDATE_INTERVAL = 5000;

// ─────────────────────────────────────────────────────────────────────────────
// Init + auth (same flow as the dev's original)
// ─────────────────────────────────────────────────────────────────────────────

void initializeSpotify() {
    Serial.printf("[DEBUG] Free heap: %d, Largest free block: %d\n",
        ESP.getFreeHeap(), heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
    Serial.println("[SPOTIFY] Initializing...");
    initializeButtons();
    Serial.println("[SPOTIFY] Init complete");
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

// ─────────────────────────────────────────────────────────────────────────────
// Now playing
// ─────────────────────────────────────────────────────────────────────────────

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
        // ...print block unchanged
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Controls
// ─────────────────────────────────────────────────────────────────────────────

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

// ─────────────────────────────────────────────────────────────────────────────
// Controls — extended
// ─────────────────────────────────────────────────────────────────────────────

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

// ── Shuffle ──────────────────────────────────────────────────────────────────

void enableShuffle() {
    response res = sp.toggle_shuffle(spotify_types::SHUFFLE_ON);
    Serial.print("[SPOTIFY] Shuffle ON: "); Serial.println(res.status_code);
}

void disableShuffle() {
    response res = sp.toggle_shuffle(spotify_types::SHUFFLE_OFF);
    Serial.print("[SPOTIFY] Shuffle OFF: "); Serial.println(res.status_code);
}

// ── Repeat ───────────────────────────────────────────────────────────────────
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

// ─────────────────────────────────────────────────────────────────────────────
// Button handling
// ─────────────────────────────────────────────────────────────────────────────

static void handleButtons() {
    if (!buttonsReady) return;

    if (pollButtonPressed(playBtn))  pauseCurrentlyPlaying();
    if (pollButtonPressed(prevBtn))  playPreviousSong();
    if (pollButtonPressed(nextBtn))  playNextSong();
}

// ─────────────────────────────────────────────────────────────────────────────
// Update — call from loop()
// ─────────────────────────────────────────────────────────────────────────────

void updateSpotify() {
    handleButtons();

    if (millis() - lastUpdate >= SPOTIFY_UPDATE_INTERVAL) {
        lastUpdate = millis();
        getCurrentlyPlaying();
    }
}