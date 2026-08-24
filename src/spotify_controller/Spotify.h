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

void initializeSpotify();

bool authenticateSpotify();

void updateSpotify();

//Helper functions
void getCurrentlyPlaying();

void pauseCurrentlyPlaying();

void playNextSong();

void playPreviousSong();

void setVolume(int volume_level);

void seekToPosition(int position_level);

void enableShuffling();

void disableShuffling();

void disableRepeat();

void enableRepeat();

void repeatOne();

//spotify information
void getAvailableDevices();

void getAlbumCover();

void searchSong(const char* song_name);

void getUserPlaylists();