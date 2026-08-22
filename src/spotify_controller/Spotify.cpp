#include "Spotify.h"

// ─────────────────────────────────────────────────────────────────────────────
// Spotify credentials
// ─────────────────────────────────────────────────────────────────────────────

const char* CLIENT_ID     = "09f8277699b4417d94cdf4fe020f7c8d";
const char* CLIENT_SECRET = "ca8a843f59b94024ac275bec538e09b9";
const char* REFRESH_TOKEN = "AQClrI3ajkedk7YEkECvEe0ZW0Yvg8FQZlELtn8_BOpHdKIQtkWN4tf46-Mo2okZ0o7Zr6GdF_NzM2e3XhZhZBgnTXjhzlCewXAq7uUG3DySV1kmSKjopOYmoxlp9G8qeSg";

// ─────────────────────────────────────────────────────────────────────────────
// Spotify instance
// ─────────────────────────────────────────────────────────────────────────────

Spotify sp(
    CLIENT_ID,
    CLIENT_SECRET,
    REFRESH_TOKEN
);

// ─────────────────────────────────────────────────────────────────────────────
// Hardware
//
// ⚠️ PLACEHOLDER PINS — confirm against the actual LCDWIKI schematic/pinout
// table before flashing. Do NOT reuse: 10,11,12,13 (display SPI),
// 15,16,17,18 (touch I2C/reset), 45 (backlight), 38/39/40/41/47/48 (SD bus),
// 9 (battery ADC), 0 (boot strap), or the USB/TX0/RX0 pins.
// ─────────────────────────────────────────────────────────────────────────────

const int PLAY_BUTTON = -1;   // TODO: set to a confirmed free GPIO
const int PREV_BUTTON = -1;   // TODO: set to a confirmed free GPIO
const int NXT_BUTTON  = -1;   // TODO: set to a confirmed free GPIO

// ─────────────────────────────────────────────────────────────────────────────
// Button state (polling + debounce, no interrupts)
// ─────────────────────────────────────────────────────────────────────────────

struct ButtonState {
    int pin;
    bool lastReading   = HIGH;   // raw pin state from the previous poll
    bool debounced      = HIGH;  // stable, debounced state
    unsigned long lastChangeMs = 0;

    ButtonState(int p) : pin(p) {}
};

static const unsigned long DEBOUNCE_MS = 30;

static ButtonState playBtn { PLAY_BUTTON };
static ButtonState prevBtn { PREV_BUTTON };
static ButtonState nextBtn { NXT_BUTTON };

// Returns true exactly once, on the falling edge (press), after debounce settles.
static bool pollButtonPressed(ButtonState &btn) {

    bool reading = digitalRead(btn.pin);

    if (reading != btn.lastReading) {
        btn.lastChangeMs = millis();
        btn.lastReading = reading;
    }

    if ((millis() - btn.lastChangeMs) > DEBOUNCE_MS) {
        if (reading != btn.debounced) {
            btn.debounced = reading;
            if (btn.debounced == LOW) {
                return true; // fresh press detected
            }
        }
    }

    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// Playback state
// ─────────────────────────────────────────────────────────────────────────────

String lastTrack  = "";
String lastArtist = "";
bool lastPlaying   = false;

// ─────────────────────────────────────────────────────────────────────────────
// Timing
// ─────────────────────────────────────────────────────────────────────────────

unsigned long lastUpdate = 0;
const unsigned long SPOTIFY_UPDATE_INTERVAL = 2000;

// ─────────────────────────────────────────────────────────────────────────────
// Button initialization
// ─────────────────────────────────────────────────────────────────────────────

static void initializeButtons() {

    pinMode(PLAY_BUTTON, INPUT_PULLUP);
    pinMode(PREV_BUTTON, INPUT_PULLUP);
    pinMode(NXT_BUTTON,  INPUT_PULLUP);

    playBtn.pin = PLAY_BUTTON;
    prevBtn.pin = PREV_BUTTON;
    nextBtn.pin = NXT_BUTTON;
}

// ─────────────────────────────────────────────────────────────────────────────
// Spotify initialization
// ─────────────────────────────────────────────────────────────────────────────

void initializeSpotify() {

    Serial.println("[SPOTIFY] Initializing...");

    initializeButtons();

    Serial.println("[SPOTIFY] Buttons initialized");

    /*
     * Authentication will eventually be handled through
     * the Wavelet Companion App.
     *
     * For now, authentication can be initialized here
     * when credentials are available.
     */

    Serial.println("[SPOTIFY] Initialization complete");
}

// ─────────────────────────────────────────────────────────────────────────────
// Authentication
// ─────────────────────────────────────────────────────────────────────────────

bool authenticateSpotify() {

    Serial.println("[SPOTIFY] Starting authentication...");

    sp.begin();

    while (!sp.is_auth()) {
        sp.handle_client();
        delay(10);
    }

    Serial.println("[SPOTIFY] Authenticated!");

    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// Currently playing
// ─────────────────────────────────────────────────────────────────────────────

void getCurrentlyPlaying() {

    bool playing = sp.is_playing();
    String track  = sp.current_track_name();
    String artist = sp.current_artist_names();

    if (playing != lastPlaying || track != lastTrack || artist != lastArtist) {

        lastTrack  = track;
        lastArtist = artist;
        lastPlaying = playing;

        #ifdef DEBUG
        Serial.println();
        Serial.println("==========");
        Serial.println(lastPlaying ? "▶ Playing" : "⏸ Paused");
        Serial.println(lastArtist);
        Serial.println(lastTrack);
        Serial.println("==========");
        #endif
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Playback controls
// ─────────────────────────────────────────────────────────────────────────────

void pauseCurrentlyPlaying() {

    if (sp.is_playing()) {
        response res = sp.pause_playback();
        Serial.print("[SPOTIFY] Pause: ");
        Serial.println(res.status_code);
    } else {
        response res = sp.start_a_users_playback();
        Serial.print("[SPOTIFY] Resume: ");
        Serial.println(res.status_code);
    }
}

void playNextSong() {
    response res = sp.skip_to_next();
    Serial.print("[SPOTIFY] Next: ");
    Serial.println(res.status_code);
}

void playPreviousSong() {
    response res = sp.skip_to_previous();
    Serial.print("[SPOTIFY] Previous: ");
    Serial.println(res.status_code);
}

void setVolume(int volume_level) {
    response res = sp.set_volume(volume_level);
    Serial.print("[SPOTIFY] Volume: ");
    Serial.println(res.status_code);
}

void seekToPosition(int position_level) {
    response res = sp.seek_to_position(position_level);
    Serial.print("[SPOTIFY] Seek: ");
    Serial.println(res.status_code);
}

// ─────────────────────────────────────────────────────────────────────────────
// Shuffle / Repeat
// ─────────────────────────────────────────────────────────────────────────────

void enableShuffling() {
    response res = sp.toggle_shuffle(spotify_types::SHUFFLE_ON);
    Serial.print("[SPOTIFY] Shuffle ON: ");
    Serial.println(res.status_code);
}

void disableShuffling() {
    response res = sp.toggle_shuffle(spotify_types::SHUFFLE_OFF);
    Serial.print("[SPOTIFY] Shuffle OFF: ");
    Serial.println(res.status_code);
}

void disableRepeat() {
    response res = sp.set_repeat_mode(spotify_types::REPEAT_OFF);
    Serial.print("[SPOTIFY] Repeat OFF: ");
    Serial.println(res.status_code);
}

void enableRepeat() {
    response res = sp.set_repeat_mode(spotify_types::REPEAT_TRACK);
    Serial.print("[SPOTIFY] Repeat TRACK: ");
    Serial.println(res.status_code);
}

void repeatOne() {
    response res = sp.set_repeat_mode(spotify_types::REPEAT_CONTEXT);
    Serial.print("[SPOTIFY] Repeat CONTEXT: ");
    Serial.println(res.status_code);
}

// ─────────────────────────────────────────────────────────────────────────────
// Spotify information
// ─────────────────────────────────────────────────────────────────────────────

void getAvailableDevices() {
    Serial.print("[SPOTIFY] Current device ID: ");
    Serial.println(sp.current_device_id());
    response res = sp.get_available_devices();
    print_response(res);
}

void getAlbumCover() {
    Serial.println("[SPOTIFY] Album cover:");
    Serial.println(sp.get_current_album_image_url(0));
}

void searchSong(const char* song_name) {
    Serial.print("[SPOTIFY] Searching: ");
    Serial.println(song_name);
    response res = sp.search_for_item(song_name, "song");
    print_response(res);
}

void getUserPlaylists() {
    response res = sp.get_current_users_playlists();
    print_response(res);
}

// ─────────────────────────────────────────────────────────────────────────────
// Button handling — polled, debounced, no interrupts
// ─────────────────────────────────────────────────────────────────────────────

static void handleButtons() {

    if (pollButtonPressed(playBtn)) {
        pauseCurrentlyPlaying();
        Serial.println("[SPOTIFY] Play button pressed");
    }

    if (pollButtonPressed(prevBtn)) {
        playPreviousSong();
        Serial.println("[SPOTIFY] Previous button pressed");
    }

    if (pollButtonPressed(nextBtn)) {
        playNextSong();
        Serial.println("[SPOTIFY] Next button pressed");
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Update
// ─────────────────────────────────────────────────────────────────────────────

void updateSpotify() {

    handleButtons();

    if (millis() - lastUpdate >= SPOTIFY_UPDATE_INTERVAL) {
        lastUpdate = millis();
        getCurrentlyPlaying();
    }
}