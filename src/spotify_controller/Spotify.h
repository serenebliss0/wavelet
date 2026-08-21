#pragma once

#include <Arduino.h>
#include "SpotifyEsp32.h"

// ─────────────────────────────────────────────────────────────────────────────
// Spotify
// ─────────────────────────────────────────────────────────────────────────────

extern const char* CLIENT_ID;
extern const char* CLIENT_SECRET;
extern const char* REFRESH_TOKEN;

extern Spotify sp;

// ─────────────────────────────────────────────────────────────────────────────
// Hardware
// ─────────────────────────────────────────────────────────────────────────────

extern const int PLAY_BUTTON;
extern const int PREV_BUTTON;
extern const int NXT_BUTTON;

extern volatile bool play_buttonPressed;
extern volatile bool prev_buttonPressed;
extern volatile bool next_buttonPressed;

// ─────────────────────────────────────────────────────────────────────────────
// Playback state
// ─────────────────────────────────────────────────────────────────────────────

extern String lastTrack;
extern String lastArtist;
extern bool lastPlaying;

// ─────────────────────────────────────────────────────────────────────────────
// Initialization
// ─────────────────────────────────────────────────────────────────────────────

void initializeSpotify();

// ─────────────────────────────────────────────────────────────────────────────
// Authentication
// ─────────────────────────────────────────────────────────────────────────────

bool authenticateSpotify();

// ─────────────────────────────────────────────────────────────────────────────
// Update
// ─────────────────────────────────────────────────────────────────────────────

void updateSpotify();

// ─────────────────────────────────────────────────────────────────────────────
// Playback
// ─────────────────────────────────────────────────────────────────────────────

void getCurrentlyPlaying();

void pauseCurrentlyPlaying();

void playNextSong();

void playPreviousSong();

void setVolume(int volume_level);

void seekToPosition(int position_level);

// ─────────────────────────────────────────────────────────────────────────────
// Shuffle
// ─────────────────────────────────────────────────────────────────────────────

void enableShuffling();

void disableShuffling();

// ─────────────────────────────────────────────────────────────────────────────
// Repeat
// ─────────────────────────────────────────────────────────────────────────────

void disableRepeat();

void enableRepeat();

void repeatOne();

// ─────────────────────────────────────────────────────────────────────────────
// Spotify information
// ─────────────────────────────────────────────────────────────────────────────

void getAvailableDevices();

void getAlbumCover();

void searchSong(const char* song_name);

void getUserPlaylists();