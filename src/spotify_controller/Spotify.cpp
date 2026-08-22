#include "Spotify.h"

// ─────────────────────────────────────────────────────────────────────────────
// Spotify credentials
// ─────────────────────────────────────────────────────────────────────────────

const char* CLIENT_ID = "";
const char* CLIENT_SECRET = "";
const char* REFRESH_TOKEN = "";

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
// ─────────────────────────────────────────────────────────────────────────────

const int PLAY_BUTTON = 15;
const int PREV_BUTTON = 21;
const int NXT_BUTTON = 19;

// ─────────────────────────────────────────────────────────────────────────────
// Button state
// ─────────────────────────────────────────────────────────────────────────────

volatile bool play_buttonPressed = false;
volatile bool prev_buttonPressed = false;
volatile bool next_buttonPressed = false;

// ─────────────────────────────────────────────────────────────────────────────
// Playback state
// ─────────────────────────────────────────────────────────────────────────────

String lastTrack = "";
String lastArtist = "";
bool lastPlaying = false;

// ─────────────────────────────────────────────────────────────────────────────
// Timing
// ─────────────────────────────────────────────────────────────────────────────

unsigned long lastUpdate = 0;

const unsigned long SPOTIFY_UPDATE_INTERVAL = 2000;

// ─────────────────────────────────────────────────────────────────────────────
// Interrupt handlers
// ─────────────────────────────────────────────────────────────────────────────

void IRAM_ATTR play_buttonISR() {
    play_buttonPressed = true;
}

void IRAM_ATTR prev_buttonISR() {
    prev_buttonPressed = true;
}

void IRAM_ATTR next_buttonISR() {
    next_buttonPressed = true;
}

// ─────────────────────────────────────────────────────────────────────────────
// Button initialization
// ─────────────────────────────────────────────────────────────────────────────

static void initializeButtons() {

    pinMode(
        PLAY_BUTTON,
        INPUT_PULLUP
    );

    pinMode(
        PREV_BUTTON,
        INPUT_PULLUP
    );

    pinMode(
        NXT_BUTTON,
        INPUT_PULLUP
    );

    attachInterrupt(
        digitalPinToInterrupt(PLAY_BUTTON),
        play_buttonISR,
        FALLING
    );

    attachInterrupt(
        digitalPinToInterrupt(PREV_BUTTON),
        prev_buttonISR,
        FALLING
    );

    attachInterrupt(
        digitalPinToInterrupt(NXT_BUTTON),
        next_buttonISR,
        FALLING
    );
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

    /*
     * Temporary authentication flow.
     *
     * This will eventually be replaced with credentials
     * provisioned by the Wavelet Companion App.
     */

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

    String track = sp.current_track_name();
    String artist = sp.current_artist_names();

    if (
        playing != lastPlaying ||
        track != lastTrack ||
        artist != lastArtist
    ) {

        lastTrack = track;
        lastArtist = artist;
        lastPlaying = playing;

        #ifdef DEBUG

        Serial.println();
        Serial.println("==========");

        Serial.println(
            lastPlaying
                ? "▶ Playing"
                : "⏸ Paused"
        );

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

        response res =
            sp.pause_playback();

        Serial.print(
            "[SPOTIFY] Pause: "
        );

        Serial.println(
            res.status_code
        );

    } else {

        response res =
            sp.start_a_users_playback();

        Serial.print(
            "[SPOTIFY] Resume: "
        );

        Serial.println(
            res.status_code
        );
    }
}

// ─────────────────────────────────────────────────────────────────────────────

void playNextSong() {

    response res =
        sp.skip_to_next();

    Serial.print(
        "[SPOTIFY] Next: "
    );

    Serial.println(
        res.status_code
    );
}

// ─────────────────────────────────────────────────────────────────────────────

void playPreviousSong() {

    response res =
        sp.skip_to_previous();

    Serial.print(
        "[SPOTIFY] Previous: "
    );

    Serial.println(
        res.status_code
    );
}

// ─────────────────────────────────────────────────────────────────────────────

void setVolume(int volume_level) {

    response res =
        sp.set_volume(volume_level);

    Serial.print(
        "[SPOTIFY] Volume: "
    );

    Serial.println(
        res.status_code
    );
}

// ─────────────────────────────────────────────────────────────────────────────

void seekToPosition(int position_level) {

    response res =
        sp.seek_to_position(position_level);

    Serial.print(
        "[SPOTIFY] Seek: "
    );

    Serial.println(
        res.status_code
    );
}

// ─────────────────────────────────────────────────────────────────────────────
// Shuffle
// ─────────────────────────────────────────────────────────────────────────────

void enableShuffling() {

    response res =
        sp.toggle_shuffle(
            spotify_types::SHUFFLE_ON
        );

    Serial.print(
        "[SPOTIFY] Shuffle ON: "
    );

    Serial.println(
        res.status_code
    );
}

// ─────────────────────────────────────────────────────────────────────────────

void disableShuffling() {

    response res =
        sp.toggle_shuffle(
            spotify_types::SHUFFLE_OFF
        );

    Serial.print(
        "[SPOTIFY] Shuffle OFF: "
    );

    Serial.println(
        res.status_code
    );
}

// ─────────────────────────────────────────────────────────────────────────────
// Repeat
// ─────────────────────────────────────────────────────────────────────────────

void disableRepeat() {

    response res =
        sp.set_repeat_mode(
            spotify_types::REPEAT_OFF
        );

    Serial.print(
        "[SPOTIFY] Repeat OFF: "
    );

    Serial.println(
        res.status_code
    );
}

// ─────────────────────────────────────────────────────────────────────────────

void enableRepeat() {

    response res =
        sp.set_repeat_mode(
            spotify_types::REPEAT_TRACK
        );

    Serial.print(
        "[SPOTIFY] Repeat TRACK: "
    );

    Serial.println(
        res.status_code
    );
}

// ─────────────────────────────────────────────────────────────────────────────

void repeatOne() {

    response res =
        sp.set_repeat_mode(
            spotify_types::REPEAT_CONTEXT
        );

    Serial.print(
        "[SPOTIFY] Repeat CONTEXT: "
    );

    Serial.println(
        res.status_code
    );
}

// ─────────────────────────────────────────────────────────────────────────────
// Spotify information
// ─────────────────────────────────────────────────────────────────────────────

void getAvailableDevices() {

    Serial.print(
        "[SPOTIFY] Current device ID: "
    );

    Serial.println(
        sp.current_device_id()
    );

    response res =
        sp.get_available_devices();

    print_response(res);
}

// ─────────────────────────────────────────────────────────────────────────────

void getAlbumCover() {

    Serial.println(
        "[SPOTIFY] Album cover:"
    );

    Serial.println(
        sp.get_current_album_image_url(0)
    );
}

// ─────────────────────────────────────────────────────────────────────────────

void searchSong(const char* song_name) {

    Serial.print(
        "[SPOTIFY] Searching: "
    );

    Serial.println(song_name);

    response res =
        sp.search_for_item(
            song_name,
            "song"
        );

    print_response(res);
}

// ─────────────────────────────────────────────────────────────────────────────

void getUserPlaylists() {

    response res =
        sp.get_current_users_playlists();

    print_response(res);
}

// ─────────────────────────────────────────────────────────────────────────────
// Button handling
// ─────────────────────────────────────────────────────────────────────────────

static void handleButtons() {

    if (play_buttonPressed) {

        play_buttonPressed = false;

        pauseCurrentlyPlaying();

        Serial.println(
            "[SPOTIFY] Play button pressed"
        );
    }

    if (prev_buttonPressed) {

        prev_buttonPressed = false;

        playPreviousSong();

        Serial.println(
            "[SPOTIFY] Previous button pressed"
        );
    }

    if (next_buttonPressed) {

        next_buttonPressed = false;

        playNextSong();

        Serial.println(
            "[SPOTIFY] Next button pressed"
        );
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Update
// ─────────────────────────────────────────────────────────────────────────────

void updateSpotify() {

    handleButtons();

    if (
        millis() - lastUpdate >=
        SPOTIFY_UPDATE_INTERVAL
    ) {

        lastUpdate = millis();

        getCurrentlyPlaying();
    }
}