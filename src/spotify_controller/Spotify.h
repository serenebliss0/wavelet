#pragma once

#include <Arduino.h>
#include "SpotifyEsp32.h"

extern const char* CLIENT_ID;
extern const char* CLIENT_SECRET;
extern const char* REFRESH_TOKEN;

extern Spotify sp;

extern String lastTrack;
extern String lastArtist;
extern bool lastPlaying;
extern int lastProgressMs;
extern int lastDurationMs;
extern int lastSpotifyVolume;
extern String lastPlayingDevice;

void initializeSpotify();

bool authenticateSpotify();

String updateSpotify();

//Helper functions
String getCurrentlyPlaying();

void pauseCurrentlyPlaying();

void playNextSong();

void playPreviousSong();

void setVolume(int volume_level);

void seekToPosition(int position_level);
void setSpotifyFeatureEnabled(bool enabled);
void updateSpotifyMediaUi();

void enableShuffle();

void disableShuffle();

void setRepeatOff();

void setRepeatTrack();

void setRepeatContext();

//spotify information
void getAvailableDevices();

void getAlbumCover();

void searchSong(const char* song_name);

void getUserPlaylists();
