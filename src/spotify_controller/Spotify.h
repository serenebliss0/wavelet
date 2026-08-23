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
//
// Buttons are handled by polling (see Spotify.cpp) — no interrupts, so no
// volatile flags need to be exposed here.
// ─────────────────────────────────────────────────────────────────────────────

extern const int PLAY_BUTTON;
extern const int PREV_BUTTON;
extern const int NXT_BUTTON;

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